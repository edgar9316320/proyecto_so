#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char **argv)
{


	  if(argc<2)
	  {
	    printf("%s [puerto]\n",argv[0]);
	    return 1;
	  }


	int conexionServidor, ret, puerto;
	struct sockaddr_in servidor;

	int conexionCliente;
	struct sockaddr_in cliente;

	socklen_t longCliente;

	char buffer[1024], buffer2[1024];
	pid_t p_hijo;

	puerto = atoi(argv[1]);

	conexionServidor = socket(AF_INET, SOCK_STREAM, 0);
	if(conexionServidor < 0){
		printf("Error en Conexion.\n");
		exit(1);
	}
	printf("Socket de Servidor Esta Creado.\n");

	memset(&servidor, '\0', sizeof(servidor));
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(puerto);
	servidor.sin_addr.s_addr = INADDR_ANY;

	ret = bind(conexionServidor, (struct sockaddr*)&servidor, sizeof(servidor));
	if(ret < 0){
		printf("Error en union.\n");
		exit(1);
	}
	printf("Union a Puerto %d\n", puerto);

	if(listen(conexionServidor, 10) == 0){
		printf("Escuchando....\n");
	}else{
		printf("Error al Escuchar.\n");
	}


	while(1){
		conexionCliente = accept(conexionServidor, (struct sockaddr*)&cliente, &longCliente);
		if(conexionCliente < 0){
			exit(1);
		}
		printf("Conexion aceptada de %s:%d\n", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port));

		if((p_hijo = fork()) == 0){
			close(conexionServidor);

			while(1){
				recv(conexionCliente, buffer, 1024, 0);
				if(strcmp(buffer, ":salir") == 0){
					printf("Desconexion de %s:%d\n", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port));
					break;
				}else{
					fgets(buffer2, 1024, stdin);
					printf("Cliente: %s\n", buffer);
					if (strcmp(buffer2, "") == 0)
					{
						send(conexionCliente, buffer, strlen(buffer), 0);
						bzero(buffer, sizeof(buffer));
					}else
					{
						send(conexionCliente, buffer2, strlen(buffer2), 0);
						bzero(buffer, sizeof(buffer));
					}
					
					

				}
								  
			}
		}

	}

	close(conexionCliente);


	return 0;
}