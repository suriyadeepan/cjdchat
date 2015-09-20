#include "cjdchat.h"

#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "string.h"

#include "cjdns/cjdns.h"
#include "model/model.h"
#include "net/ipv6socket.h"
#include "cntl/cntl.h"

#include "iostream"
#include "string"
#include "vector"

using namespace std;

// list of peers(ipv6)
vector<string> ip_list;
// pointer to model (array of nodes)
Node **model = NULL;
int peer_count = 0;

char SELF_NICK[15];

//


int main(){


// >>-------------------------------------<<
// int cjdns_getPeers(vector<string> *ip_list)
//  //should fill vector with IPV6 addresses and 
//  //  return the number of peers 'peer_count'
// model = (Node **)malloc( peer_count * sizeof (Node *) )
// 	//allocate memory to model to model array
//  //Call model_init(&ip_list,&model);
// >>-------------------------------------<<

	
	// get the peers (IPV6)
	peer_count = cjdns_getPeers(&ip_list);

	pthread_t getPeers_thread;
	pthread_create(&getPeers_thread, NULL, cjdns_trackPeers, NULL);

	printf("---------------");
	for(int i=0;i<peer_count;i++)
		printf("\nIP : %s",ip_list[i].c_str());
	printf("\n---------------");

	/*if(peer_count == -1){
		printf("\n>> ERROR : check if cjdroute is running\n>> Command : cjstart\n");
		return -1;
	}*/

	printf("\n>> peer_count : %d\n",peer_count);
	// alloc memory for model
	model = (Node**)malloc(sizeof(Node *) * peer_count); 	
	// update model with peers' IPV6
	model_init(model,&ip_list);
	model_echo(model,peer_count);

	// create a thread that listens to port LISTEN_PORT
	pthread_t listen_thread;
	pthread_create(&listen_thread, NULL, ipv6socket_listen, NULL);

	// get nick
	printf("\n>> Enter nick : ");
	scanf("%s",SELF_NICK);
	pthread_t send_thread;

	model_echo(model,peer_count);
	for(int i=1;i<peer_count;i++){
		pthread_create(&send_thread, NULL, ipv6socket_joinMsg,(void *)(model[i]->address));
	}

	while(1){
	  char msg[100], formatted_msg[100];
	  printf("\n>>");
	  scanf("%s",msg);

	  pthread_t broadcast_thread, unicast_thread;


		int msg_stat = cntl_splitter(msg,formatted_msg);

		printf("\nMSG_STAT : %d",msg_stat);

		switch(msg_stat){
			case MSG: // private message
				pthread_create(&unicast_thread, NULL, ipv6socket_unicast,(void *)(formatted_msg));
				break;


			case QUIT:
				printf("\n>> @%s quit the network\n",SELF_NICK);
				pthread_create(&broadcast_thread, NULL, ipv6socket_broadcast,(void *)(msg));
				return 0;
				break;

			default:
				pthread_create(&broadcast_thread, NULL, ipv6socket_broadcast,(void *)(msg));
		}// switch ends here


	}

	//while(1);

	pthread_exit(NULL);
	return 0;

}
