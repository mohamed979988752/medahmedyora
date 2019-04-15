
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include<pthread.h>
#include <string.h>
#define PORT 8080
pthread_mutex_t lock;
int sock;
char Buffer[1024] ;

static struct sockaddr_in sin;
struct sockaddr_in clientsin;	
int montant=50;
	
void * section_critique(void*);
int main()
{
int ret;
int clientsock;
int i ,cpt,arg;
pthread_t th[5];
int recsize = (int) sizeof clientsin;

	
	

	/* Si les sockets Windows fonctionnent */
	
		sock = socket(AF_INET, SOCK_STREAM, 0);

		/* Si la socket est valide */
		if (sock != -1)
		{
			printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

			/* Configuration */
			memset(&sin,'\0',sizeof (sin));
			sin.sin_addr.s_addr = htonl(INADDR_ANY);   /* Adresse IP automatique */
			sin.sin_family = AF_INET;             /* Protocole familial (IP) */
			sin.sin_port = htons(PORT);         /* Listage du port */
			ret = bind(sock, (struct sockaddr *)&sin, sizeof (sin));
			

			/* Si la socket fonctionne */
			
				/* Démarrage du listage (mode server) */
				if ( listen(sock, 3)==0)
				printf("Listage du port %d...\n", PORT);
				if (pthread_mutex_init(&lock, NULL) != 0)
 				{
  			      printf("\n mutex init failed\n");
  			      return 1;
  				}
  				
  				printf("premier montant débuté est : %d DT\n" , montant);
			
						while (1)
					{
						for (i=0;i<3;i++){
						clientsock = accept(sock, (struct sockaddr*)&clientsin, &recsize);
				
						if (clientsock < 0) 
							{
								exit(1);
							}
						if ((cpt=pthread_create (&th[i],NULL,section_critique,(void *)&clientsock))!=0)
							{
								printf("%s\n",strerror(1) );
								exit(1);
							}
					
						

					}
					close(sock);
				}
					for (int j=0;i<3;i++)
					{
							pthread_join(th[i],NULL);

					}
				/* Fermeture de la socket */
			printf("Fermeture de la socket...\n");
			close(sock);
			printf("Fermeture du serveur terminee\n");
					
		}

	return 0;
}

void * section_critique(void * arg){
	
	int csock=*((int *)arg);
	int sock;
	int x;

						printf("Un client se connecte avec la socket %d de :%d\n", csock, htons(clientsin.sin_port));
						
						//mutex lock
						pthread_mutex_lock(&lock);
						while(recv(csock, Buffer, 1024, 0))
							{
								
								
								x=atoi(Buffer);
								if (x<=montant ){
									printf("Ce client a entrée un montant inacceptable.\n Disconnected from %s %d\n",inet_ntoa(clientsin.sin_addr),ntohs(clientsin.sin_port));
									close (csock);
									break;
								}
								else 
									{
										printf("client : %d DT\n",x);
										montant=x;
										send(csock, Buffer, strlen(Buffer), 0);
										bzero(Buffer,sizeof (Buffer));
								
									}

						
							}
							
						//mutex inlock
						pthread_mutex_unlock(&lock);
						
						pthread_exit(NULL);


}