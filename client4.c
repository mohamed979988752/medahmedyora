#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080


int main()
{
	
	int sock;
	struct sockaddr_in sin;
	char Buffer[1024] ;
	int rep,x,montant=50;
	
	
		/* Création de la socket */
		sock = socket(AF_INET, SOCK_STREAM, 0);

		/* Configuration de la connexion */
		sin.sin_addr.s_addr = inet_addr("192.168.43.186");
		sin.sin_family = AF_INET;
		sin.sin_port = htons(PORT);

		/* Si l'on a réussi à se connecter */
		rep = connect(sock, (struct sockaddr *)&sin, sizeof(sin));
		/*  on affiche "Impossible de se connecter" */
		
	
		/*CONNEXION ETABLIE */
		printf("Connection à %s  sur le port %d\n",inet_ntoa(sin.sin_addr), htons(sin.sin_port));
		printf("Bienvenue dans notre enchère...\n");
		printf("premier montant débuté est : %d DT\n" , montant);
		/* section critique */
		while (1) {
			
			printf("ajouter votre montant (tapez 'non' pour quitter)\n");
			printf("Client : ");
			scanf("%s",Buffer);
			
			send(sock, Buffer, 1024, 0);
		
			if (strcmp(Buffer, "non") == 0) {
				
				printf("disconnected from server\n");
				exit(1);
			}
			x=atoi(Buffer);
			recv(sock, Buffer, 1024, 0) ;
			
			if (x<=montant){
				printf("Votre montant inacceptable.\n Disconnected from %s %d\n",inet_ntoa(sin.sin_addr),ntohs(sin.sin_port));
				close (sock);
				break;
			}
			else
			{
				montant=x;
			 printf("server : dernier nontant donnée est %d DT \n", montant); 
			}
			}
			
		
		close(sock);

			
	
		return 0;
}


