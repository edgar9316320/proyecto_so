all : servidor cliente

CPPFLAGS = -g -I.

servidor : servidor.c
	cc -g -I. servidor.c -o servidor

cliente : cliente.c
	cc -g -I. cliente.c -o cliente

clean :
	rm cliente servidor
