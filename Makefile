compile: server.c client.c
	gcc cards.c client.c -o client
	gcc cards.c server.c -o server
