import java.net.*;
import java.io.*;
public class TcpServer
{
    public static void main(String args[]) throws IOException
       {
            ServerSocket s = new ServerSocket();
            // povezi soket servera sa hostom i portom na kojemu ce slusati
            s.bind(new InetSocketAddress ("127.0.0.1", 50076));
            System.out.println("Soket kreiran na portu 50076!");
            while(true) // beskonacna petlja (server ceka konekcije)
            {
                System.out.println("Cekam na novu konekciju...");
                Socket s1 = s.accept();
                OutputStream s1out = s1.getOutputStream();
                DataOutputStream dos = new DataOutputStream(s1out);
                InputStream s1In = s1.getInputStream();
                BufferedReader dis = new BufferedReader(new InputStreamReader(s1In));
                String st = new String(dis.readLine());
                System.out.println("Primljeno: " + st);
                // broj koji je server primio biti ce rastavljen na tokene
                // (npr. ako je klijent poslao serveru broj 23, server ce primiti slijedece
                // \02\03\0)
                // izbrisati cemo sve znakove \0 iz stringa koristenjem regularnih izraza
                String result = st.replaceAll("\0", ""); // regex
                System.out.println("rezultat: " + result);
                // sami nadopisite sljedeci kod 
                // 1. konvertiraj string u float

                // 2. posalji rezultate klijentu
                // (moze biti u obliku string, ne trebate slati float)
       
                dos.close();
                dis.close();
                s1out.close();
                s1.close();
            }
        }
}
