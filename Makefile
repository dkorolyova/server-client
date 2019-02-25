all: clean_all link_server link_client
ifeq ($(OS),Windows_NT)
link_server: platform.o network.o server.o functions_server.o
	gcc server.o platform.o network.o functions_server.o -o server_app -lws2_32

link_client: platform.o network.o client.o functions_client.o
	gcc client.o platform.o network.o functions_client.o -o client_app -lws2_32
else
link_server: platform.o network.o server.o functions_server.o file_sorter.o
	gcc server.o platform.o network.o functions_server.o file_sorter.o -o server_app

link_client: platform.o network.o client.o functions_client.o
	gcc client.o platform.o network.o functions_client.o -o client_app

file_sorter.o:
	gcc -c server/file_sorter.c

endif

server.o:
	gcc -c server/server.c
platform.o:
	gcc -c shared/platform.c
network.o:
	gcc -c shared/network.c
functions_server.o:
	gcc -c server/functions_server.c

client.o:
	gcc -c client/client.c
functions_client.o:
	gcc -c client/functions_client.c

clean_all:
	rm -rf server.o functions_server.o client.o network.o platform.o functions_client.o file_sorter.o
