// naredba "import" u Javi je analogna naredbi "#include" u C-u
import java.net.*; // ukljuci sve klase definirane u paketu java.net (za rad sa soketima)
import java.io.*; // ukljuci sve klase definirane u paketu java.io (za osnovne IO, tj.
// input output, operacije)
public class TcpClient // ime glavne klase je TcpClient
{
// public: main() je prva metoda koja se poziva iz Java okruzenja i zato mora biti public
// (funkcije u Javi se nazivaju metode)
// static: Java okruzenje mora biti u stanju pozvati main() metodu bez da stvara instancu
// klase, pa zato mora biti static
// void: main() ne vraca nista
// throws IOException: kazemo kompajleru da metoda main() moze baciti IO iznimke
public static void main(String args[]) throws IOException
{
    // otvori soket klijenta prema serveru adria.fesb.hr koji slusa na portu 50076
    Socket s1 = new Socket("127.0.0.1", 50076);

    // ispisi poruku ako je soket uspjesno kreiran
    System.out.println("Klijent se spojio na port 50076!");
    // dohvati soketov tzv. input file handle i output file handle
    InputStream s1In = s1.getInputStream(); // dohvati podatke koji se salju soketu
    OutputStream s1out = s1.getOutputStream(); // salji podatke ovom soketu
    // dis = data input stream (da bi se podaci mogli primati na ovaj soket)
    BufferedReader dis = new BufferedReader(new InputStreamReader(s1In));
    // dos = data output stream (da bi se podaci mogli slati sa ovog soketa)
    DataOutputStream dos = new DataOutputStream(s1out);
    float arg = 0; // argument kojega je unio korisnik
    // (broj kojega je potrebno kvadrirati na serveru)

    try
    {
        if (args.length > 0) // ako je korisnik unio broj za kvadriranje
        {
            try{
                // ovdje umetnite kod za slanje broja serveru (koristite
                // dos.writeChars() za slanje podataka serveru, i dis.readLine()
                // konvertiraj primljeni broj (tipa String) u Float
                // args[0] je prvi argument iza imena klase
                // ovo nam je potrebno samo za provjeru je li korisnik unio
                // broj ili nesto drugo
                
                // posalji broj (tipa String) serveru
                
                
            }
            catch(NumberFormatException e)
            {
                // ako format od args[0] nije valjan
                System.err.println("Primljeni argument mora biti broj!");
                System.exit(1);
            }

            }
    }
    catch(Exception e) {
        // uhvati neku nepoznatu iznimku (i nemoj srusiti program)
    }
           
    // procitaj i ispisi String kojega nam posalje server
    String st = new String(dis.readLine());
    System.out.println(st);
    // na kraju zatvori konekciju i izadji
    dis.close();
    dos.close();
    s1In.close();
    s1out.close();
    s1.close();
 }
}
