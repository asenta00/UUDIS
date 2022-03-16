#include <iostream>		// potrebno za rad sa streamovima
#include <sstream>		// potrebno za rad sa streamovima
#include <iterator>		// potrebno za rad sa iteratorima
#include <pthread.h>		// potrebno za rad sa nitima
#include <curl/curl.h>		// potrebno za dohvacanje HTML-a
#include <stdlib.h>		// potrebno za exit()
#include <boost/regex.hpp>	// potrebno za rad sa regularnim izrazima
#include <time.h>		// potrebno za sleep()

using namespace std;

// ograniciti cemo se na prvih pet linkova koje pronadjemo
vector<string> lista_pet_linkova;

// definiramo mutex (MUTual EXclusion) objekt
// slicno kriticnim dijelovima koda kojima istovremeno ne smije pristupiti vise niti
pthread_mutex_t mutex_lock;

// curl nije thread-safe za https linkove, pa cemo traziti samo http linkove (ignoriramo ftp)
// boost::regbase::normal - koristimo normalnu regex gramatiku (standard ECMA-262, ECMAScript Language Specification)
// boost::regbase::icase - ignore case
boost::regex url_regex("(http|https)://(www)\\.([a-z]+[a-z0-9%\\-]*)\\.(hr|com|net|edu|org|aspx|html)(((/[a-z0-9]+[a-z0-9%\\-]*((\\.(hr|com|net|edu|org|aspx|html))?))*)?)", boost::regbase::normal | boost::regbase::icase);
boost::regex word_regex("(znanost|fesb|split|javascript|uploads|i)", boost::regbase::normal | boost::regbase::icase);	// rijec koju trazimo po linkovima

// globalni brojac rijeci koje trazimo po linkovima
int brTrazenihRijeci = 0;

// size_t (i.e. unsigned int) vraca broj byteova podataka
size_t write_data (char *ptr, size_t size, size_t nmemb, void *userdata)
{
	// stream pokazuje na userdata iz main funkcije (void* smo pretvorili u ostringstream*)
	ostringstream *stream = (ostringstream*)userdata;

	size_t count = size * nmemb;
    	stream->write(ptr, count);

    	return count;
}

void *printMessage (void *thread_id)
{
	// cekamo malo dok nit uspije zakljucati ovaj dio koda (ako je netko prekine, doci ce do Segmentation Fault greske)
	sleep(1);

	pthread_mutex_lock(&mutex_lock); // zakljucaj ovaj dio koda

	int thread_id_2;
	thread_id_2 = (intptr_t)thread_id;	// cast je potreban zato sto je thread_id tipa (void *)

	// prikazi link koji trenutno pretrazujemo
	cout << "\nLink za nit broj " << thread_id_2 << ": " << lista_pet_linkova[thread_id_2] << endl;

	CURL *curl_handle2;

	curl_handle2 = curl_easy_init();

	ostringstream stream;

	// u strink link spremi link koji odgovara toj niti
	string link = lista_pet_linkova[thread_id_2];

	// convert link to char * jer njega prima curl_easy_setopt
	const char * link2;
	link2 = link.c_str();
	
	if (curl_handle2)
	{
		// ovaj dio koda trebate sami napisati
		
		// odredjujemo pocetnu Web stranicu
		curl_easy_setopt(curl_handle2, CURLOPT_URL, link2);

	}

	pthread_mutex_unlock(&mutex_lock); // sada otkljucaj ovaj dio koda
    	pthread_exit(NULL);
}

int main()
{
	CURL *curl_handle;

	curl_handle = curl_easy_init();

 	// HTML podatke koje dobijemo preko cURL-a proslijedimo ovome streamu i on ga prebaci u string
	ostringstream stream;
	
	if (curl_handle)
	{
		// odredjujemo pocetnu Web stranicu
		curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.fesb.unist.hr");

		/* definiramo gdje cemo zapisati HTML sadrzaj
		 *
		 * CURLOPT_WRITEFUNCTION
		 * poziva se kada postoje podaci koje treba zapisati
		 * function pointer --> size_t function(char *ptr, size_t size, size_t nmemb, void *userdata);
		 * ptr pokazuje na podatke, podaci su velicine size*nmemb, funkcija vraca broj byteova podataka
		 * userdata se namjesta pomocu CURLOPT_WRITEDATA */

		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &stream);

		curl_easy_perform(curl_handle);
		
		// prebaci HTML podatke iz stream-a u string
		string output = stream.str();
		// cout << "String: " << output << endl;

		int maxBrLinkova = 5;		// max broj linkova koje zelimo pretraziti
		int brojac_maxBrLinkova = 0;	// brojac za max broj linkova

		int noThreads = maxBrLinkova;	// koliko niti zelimo kreirati (onoliko koliko imamo linkova)
		int result = 0;			// rezultat pthread_create funkcije
		pthread_t threads[noThreads];	// kreiraj 5 niti

		boost::sregex_iterator it(output.begin(), output.end(), url_regex);
    		boost::sregex_iterator end;	// po default-u; sluzi kao end-marker ili null-marker

    		for (; it != end; ++it)
		{
			// u globalni vektor stringova spremi prvih 5 linkova
			lista_pet_linkova.push_back(it->str());

			if (brojac_maxBrLinkova < 5)	// jer zelimo samo prvih 5 linkova, ne sve
			{
				result = pthread_create(&threads[brojac_maxBrLinkova],NULL, printMessage, (void *)(intptr_t)brojac_maxBrLinkova);

				if (result != 0)	// ako nit nije uspjesno kreirana
				{
					printf("Doslo je do greske prilikom kreacije niti. Sifra greske je %d.\n", result);
					exit(-1);
				}
			}

			brojac_maxBrLinkova++;
    		}

  		cout << "Cekamo dok ne zavrsimo s dijeljenim podacima..." << endl; // i dok se ne izvrse sve niti
  		sleep(3);	// cekamo 3 sekunde

		// cleanup
		curl_easy_cleanup(curl_handle);
	}

	cout << "\nUkupan broj trazenih rijeci je: " << brTrazenihRijeci << endl;

	return 0;
}