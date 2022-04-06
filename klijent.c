#include <stdio.h>	
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	printf ("argv[0] = %s\n", argv[0]);
  	int sk;
  	struct sockaddr_in skaddr;

  	if (argc!=4)
	{
    		printf("Pokretanje: ./klijentvj <IP servera> <port> <broj>\n");
    		exit(-1);
  	}

	sk = socket(PF_INET, SOCK_STREAM, 0);

  	if (sk < 0)
	{
    		printf("Problem sa kreiranjem soketa!\n");
    		exit(-1);
  	}

  	skaddr.sin_family = AF_INET;

  	if (inet_aton(argv[1],&skaddr.sin_addr) == 0)
	{
    		printf("Kriva IP adesa: %s\n",argv[1]);
    		exit(-1);
  	}

  	skaddr.sin_port = htons(atoi(argv[2]));
  
  	if (connect(sk,(struct sockaddr *) &skaddr,sizeof(skaddr)) < 0)
	{
    		printf("Nije spojen!\n");
    		exit(-1);
  	}

 	printf("Spojio se!\n");
 	
 	
 	
 	//Ovdje umetnuti potrebni kod za slanje broja i primanje rezultata
	


 	printf("Odspojio se!\n");

  	close(sk);
	return 0;
}
