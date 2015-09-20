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
#include "../cjdchat.h"
#include "../model/model.h"
#include "../cntl/cntl.h"
//#include "../view/view.h"

//Based on http://www.abc.se/~m6695/udp.html

extern Node **model;
extern int peer_count;
extern char SELF_NICK[15];

void error(char *msg) {
	perror(msg);
	exit(1);
}

void *ipv6socket_unicast(void *msg){

	char *raw_msg = (char *)msg;
	char nick[15];
	char message[100];
	char peer_ipv6[40];

	sscanf(raw_msg,"%s %s",nick,message);

	model_nickToIp(nick,peer_ipv6);
	printf("\n$ Internal Message : Unicast %s to %s @ %s\n",nick,message,peer_ipv6);

}

void *ipv6socket_broadcast(void *msg){

	char *message;

	message = (char *)msg;

	int sockfd, portno;
	struct hostent *server;

	struct sockaddr_in6 serv_addr;
	int slen = sizeof(struct sockaddr_in6);
	int n;

	portno = LISTEN_PORT;


	for(int i=1;i<peer_count;i++){

		//Sockets Layer Call: socket()
		sockfd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
		if (sockfd < 0)
			error("ERROR opening socket");

		//Sockets Layer Call: gethostbyname2()
		server = gethostbyname2(model[i]->address,AF_INET6);
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
		n = sendto(sockfd, message, strlen(message)+1, 0, (struct sockaddr *) &serv_addr, slen);
		if (n < 0)
			error("ERROR writing to socket");

		//printf("\nString sent to server...\n");

		//Sockets Layer Call: close()
		close(sockfd);
	}

}




void *ipv6socket_joinMsg(void *ipv6_addr){

	char *peer_ipv6;  

	peer_ipv6 = (char *)ipv6_addr;

	int sockfd, portno;
	struct hostent *server;

	char buffer[256] = "/join general";
	sprintf(buffer,"/join general %s",SELF_NICK);

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

	printf("\nListening for incoming connections...\n");

/*	printf("\nEcho from listen thread:\n");
	model_echo(model,peer_count);
	printf("\n");*/

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

		char output[100];
		char nick[15];
		int msg_stat = cntl_splitter(buffer,output);
		//printf("\nRESULT : %d and MSG : %s",result,output); 

		//Sockets Layer Call: inet_ntop()
		inet_ntop(AF_INET6, &(si_other.sin6_addr),client_addr_ipv6, 100);
		//printf("Address: %s\n",client_addr_ipv6);
		//strcpy(ipv6_addr , client_addr_ipv6);  
	
		// send back to peer
		//pthread_create(&send_thread, NULL, ipv6socket_send, (void *)client_addr_ipv6);

		switch(msg_stat){

			case JOIN:
				sscanf(output,"%s %s",buffer,nick);
				printf("\n>> @%s joined network in channel #general\n",nick);
				model_addNick(client_addr_ipv6,nick);
				break;

			case QUIT:
				model_ipToNick(client_addr_ipv6,nick);
				printf("\n>> @%s quit the network\n",nick);
				break;

			case MSG:
				model_ipToNick(client_addr_ipv6,nick);
				printf("\n>> @%s <private> :: %s\n",nick,buffer);
				break;

			default:
				model_ipToNick(client_addr_ipv6,nick);
				printf("\n>> @%s :: %s\n",nick,buffer);
		}

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
