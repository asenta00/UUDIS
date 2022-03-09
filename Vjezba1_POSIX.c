#include <stdio.h>
#include <stdlib.h>	// potrebno za funkciju exit()
#include <pthread.h>	// potrebno za rad sa nitima

void *printMessage (void *thread_id)
{
	int thread_id_2;
	thread_id_2 = (int)thread_id;	// cast je potreban zato sto je
						// thread_id tipa (void *)

	printf("Javlja se nit broj %d!\n", thread_id_2);
    	pthread_exit(NULL);
}

int main()
{
	int thread_id = 0;	// identifikator niti
	int noThreads = 3;	// koliko niti zelimo kreirati
	int result = 0;		// rezultat pthread_create funkcije

	// koristi se za identifikaciju niti
	// (pthread_t je apstraktni tip podataka koji se koristi kao handle ili
	// referenca na nit)
	pthread_t threads[noThreads];

	for (thread_id = 0; thread_id < noThreads; thread_id++)
	{
		printf("main() funkcija: kreiram nit broj %d\n", thread_id);
		result = pthread_create(&threads[thread_id],
                                    NULL,
                                    printMessage,
                                    (void *)thread_id);

		if (result != 0)	// ako nit nije uspjesno kreirana
		{
			printf("Doslo je do greske prilikom kreacije niti. Sifra greske je %d.\n", result);
			exit(-1);
		}
	}

	pthread_exit(NULL);

	return 0;
}
