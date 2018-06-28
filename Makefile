all : chat_server cliente

CPPFLAGS = -g -I.

chat_server : chat_server.c
	cc -g -I. chat_server.c -O2 -lpthread -o chat_server

cliente : cliente.c
	cc -g -I. cliente.c -o cliente

clean :
	rm cliente chat_server
