#include "model.h"
#include "stdio.h"
#include "stdlib.h"


// >>-------------------------------------<<
// int cjdns_getPeers(vector<string> *ip_list)
//  //should fill vector with IPV6 addresses and 
//  //  return the number of peers 'peer_count'
// model = (Node **)malloc( peer_count * sizeof (Node *) )
// 	//allocate memory to model to model array
//  //Call model_init(&ip_list,&model);
// >>-------------------------------------<<
//
int model_init(Node* model[], vector<string> *ip_list){

	printf("\nIP_LIST_SIZE : %d\n",ip_list->size());
	/*for(int i=0;i<ip_list->size();i++){
		model[i]->address = (*ip_list)[i];
	}*/
	for(int i=0;i<ip_list->size();i++){
		model[i] = model_newNode((*ip_list)[i]);
		//model[i] = tnode;
	}

}

Node* model_newNode(string str){
	Node * tnode = (Node*)malloc(sizeof(*tnode));
	tnode->address = str;
	return  tnode;
}


/*int main(){

	return 0;
}*/
