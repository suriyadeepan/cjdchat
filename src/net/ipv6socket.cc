#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pthread.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <arpa/inet.h>

#include "ipv6socket.h"

//Based on http://www.abc.se/~m6695/udp.html

void error(char *msg) {
	perror(msg);
	exit(1);
}

void *sendMsg(void *ipv6_addr){

	char *peer_ipv6;  

	peer_ipv6 = (char *)ipv6_addr;

	int sockfd, portno;
	struct hostent *server;
	char buffer[256] = "This is a string from client!";
	struct sockaddr_in6 serv_addr;
	int slen = sizeof(struct sockaddr_in6);
	int n;

	portno = LISTEN_PORT;

	//printf("\nIPv6 UDP Client Started...\n");

	//Sockets Layer Call: socket()
	sockfd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0)
		error("ERROR opening socket");

	//Sockets Layer Call: gethostbyname2()
	server = gethostbyname2(peer_ipv6,AF_INET6);
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_port = htons(portno);
	serv_addr.sin6_flowinfo = 0;
	memmove((char *) &serv_addr.sin6_addr.s6_addr, (char *) server->h_addr, server->h_length);


	//Sockets Layer Call: sendto()
	n = sendto(sockfd, buffer, strlen(buffer)+1, 0, (struct sockaddr *) &serv_addr, slen);
	if (n < 0)
		error("ERROR writing to socket");

	printf("\nString sent to server...\n");

	//Sockets Layer Call: close()
	close(sockfd);

}

void *ipv6socket_listen(void *){

	int sockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in6 si_me, si_other;
	int slen=sizeof(struct sockaddr_in6);
	int n;
	char client_addr_ipv6[100];

	pthread_t send_thread;

	printf("\nIPv6 UDP Server Started...\n");

	while(1){
		//Sockets Layer Call: socket()	
		sockfd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
		if (sockfd < 0)
			error("ERROR opening socket");
		bzero((char *) &si_me, sizeof(si_me));
		portno = LISTEN_PORT;

		si_me.sin6_family = AF_INET6;
		si_me.sin6_addr = in6addr_any;
		si_me.sin6_port = htons(portno);
		si_me.sin6_flowinfo = 0;


		//Sockets Layer Call: bind()
		if (bind(sockfd, (struct sockaddr *) &si_me, sizeof(si_me)) < 0)
			error("ERROR on binding");


		//Sockets Layer Call: recvfrom()
		n = recvfrom(sockfd, buffer, 255, 0, (struct sockaddr *) &si_other, (socklen_t *)&slen);

		if (n < 0)
			error("ERROR reading from socket");

		//Sockets Layer Call: inet_ntop()
		inet_ntop(AF_INET6, &(si_other.sin6_addr),client_addr_ipv6, 100);
		printf("Incoming connection from client having address: %s\n",client_addr_ipv6);
		//strcpy(ipv6_addr , client_addr_ipv6);
	
		// send back to peer
		pthread_create(&send_thread, NULL, sendMsg, (void *)client_addr_ipv6);


		printf("Message from client: %s\n", buffer);

		//Sockets Layer Call: close()
		close(sockfd);

	}

	pthread_exit(NULL);

	return 0;
}

/*int main(){

	pthread_t listen_thread;
	pthread_create(&listen_thread, NULL, ipv6socket_listen, NULL);

	while(1);

	pthread_exit(NULL);

	return 0;

}*/
