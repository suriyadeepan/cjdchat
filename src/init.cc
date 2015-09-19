#include "cjdchat.h"

#include "cjdns.h"
#include "model.h"


//

int peer_count = 0;

int main(){

	vector<string> ip_list;

// >>-------------------------------------<<
// int cjdns_getPeers(vector<string> *ip_list)
//  //should fill vector with IPV6 addresses and 
//  //  return the number of peers 'peer_count'
// model = (Node **)malloc( peer_count * sizeof (Node *) )
// 	//allocate memory to model to model array
//  //Call model_init(&ip_list,&model);
// >>-------------------------------------<<

	
	peer_count = cjdns_getPeers(&ip_list);
	printf("\npeer_count : %d\n",peer_count);

	return 0;
}
