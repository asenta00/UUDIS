#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int ld, sd;			
  	struct sockaddr_in skaddr;
  	struct sockaddr_in from;	
  	socklen_t addrlen, length;

	ld = socket(PF_INET, SOCK_STREAM, 0);

  	if (ld < 0)
	{
    		printf("Problem sa kreiranjem soketa!\n");
    		exit(-1);
  	}
  
  	skaddr.sin_family = AF_INET;
  	skaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  	skaddr.sin_port = htons(50000);

	int result = 0;
	result = bind(ld, (struct sockaddr *) &skaddr, sizeof(skaddr));

  	if (result < 0)
	{
    		printf("Problem sa bindingom!\n");
		printf("Port mozda nije dostupan!\n");
    		exit(-1);
  	}
  
  	length = sizeof(skaddr);

	result = 0;
	result = getsockname(ld, (struct sockaddr *) &skaddr, &length);
  	if (result < 0)
	{
    		printf("Doslo je do greske prilikom dohvacanja imena soketa!\n");
    		exit(-1);
  	}

  	printf("Server je na portu %d\n",ntohs(skaddr.sin_port)); // network to host short

  	if (listen(ld,5) < 0)
	{
    		printf("Greska prilikom osluskivanja konekcije!\n");
    		exit(-1);
  	}

  	while (1)
	{
    		printf("Cekam na vezu ...\n");
    		addrlen = sizeof(skaddr);

		sd = accept(ld, (struct sockaddr*) &from, &addrlen);

    		if (sd < 0)
		{
      			printf("Problem sa prihvacanjem veze!\n");
      			exit(-1);
    		}

    		printf("Soketi su spojeni. Racunam ...\n");

		char buffer[20]; // max 20 znakova
		int n = 0; // broj bajtova kopiranih u buffer, 1 bajt po znaku
		n = read(sd, buffer, 20);
		printf("Broj kopiranih bajtova: %d\n", n);

		buffer[n] = '\0';
		float primljeni_broj = 0;
		primljeni_broj = atof(buffer);

		printf("Primljeni broj: %f\n", primljeni_broj);

		float kvadrirani_broj = 0;
		kvadrirani_broj = primljeni_broj * primljeni_broj;

		char rezultat[50];
		sprintf(rezultat, "%f", kvadrirani_broj);
		printf("Saljem rezultat klijentu... Rezultat je %s.\n", rezultat);
		write(sd, rezultat, strlen(rezultat));
		
    		printf("Kraj racunanja!\n\n\n");
    		close(sd);
  	}

	return 0;
}
