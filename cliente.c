#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
//Edgar Joseph Rivero Matheus C.I = 20428267
//Jesus Miguel Quinto Teran C.I = 25619081


int main(int argc, char **argv)
{

	if(argc<2)
  	{
    printf("%s [puerto]\n",argv[0]);
    return 1;
  	}


	int conexion, ret, puerto;
	struct sockaddr_in cliente;

	puerto = (atoi(argv[1]));
	  
	char buffer[1024];

	conexion = socket(AF_INET, SOCK_STREAM, 0);
	if(conexion < 0){
		printf("Error en Conexion.\n");
		exit(1);
	}
	printf("Socket del Cliente esta Creado.\n");

	memset(&cliente, '\0', sizeof(cliente));
	//bzero((char *)&cliente, sizeof((char *)&cliente));
	cliente.sin_family = AF_INET;
	cliente.sin_port = htons(puerto);
	cliente.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(conexion, (struct sockaddr*)&cliente, sizeof(cliente));
	if(ret < 0){
		printf("Error en Conexion.\n");
		exit(1);
	}
	printf("Conectado a Servidor.\n");

	while(1){
		printf("Cliente: \t");
		scanf("%s", &buffer[0]);

		send(conexion, buffer, strlen(buffer), 0);

		if(strcmp(buffer, ":salir") == 0){
			close(conexion);
			printf("Desconectado de Servidor.\n");
			exit(1);
		}

		if(recv(conexion, buffer, 1024, 0) < 0){
			printf("Error Recibiendo Datos.\n");
		}else{
			printf("Servidor: \t%s\n", buffer);
		}
	}

	return 0;
}