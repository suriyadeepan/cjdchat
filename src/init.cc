#include "cjdchat.h"

#include "stdio.h"
#include "stdlib.h"

#include "cjdns/cjdns.h"
#include "model/model.h"

#include "iostream"
#include "string"
#include "vector"

using namespace std;

// list of peers(ipv6)
vector<string> ip_list;
// pointer to model (array of nodes)
Node **model = NULL;
int peer_count = 0;

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
	printf("\n>> peer_count : %d\n",peer_count);
	// alloc memory for model
	model = (Node**)malloc(sizeof(Node *) * peer_count); 	
	// update model with peers' IPV6
	model_init(model,&ip_list);
	model_echo(model,peer_count);

	return 0;
}
