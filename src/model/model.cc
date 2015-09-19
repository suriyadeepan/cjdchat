#include "model.h"

// >>-------------------------------------<<
// int cjdns_getPeers(vector<string> *ip_list)
//  //should fill vector with IPV6 addresses and 
//  //  return the number of peers 'peer_count'
// model = (Node **)malloc( peer_count * sizeof (Node *) )
// 	//allocate memory to model to model array
//  //Call model_init(&ip_list,&model);
// >>-------------------------------------<<
//
int model_init(vector<string> *ip_list, Node* model[]){

	for(int i=0;i<ip_list->size();i++){
		model[i]->address = (*ip_list)[i];
	}

}


int main(){

	return 0;
}
