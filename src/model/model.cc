#include "model.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


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

	char tstring[40];
	
	for(int i=0;i<ip_list->size();i++){
		Node * tnode = (Node*)malloc(sizeof(*tnode));
		strcpy(tnode->address , (*ip_list)[i].c_str());
		model[i] = tnode;
	}

}

void model_echo(Node* model[],int peer_count){

	printf("\n---------------");
	for(int i=0;i< peer_count;i++)
		printf("\n%s %s %s",model[i]->address, model[i]->nick,model[i]->chan);
	printf("---------------\n");
}

/*Node* model_newNode(){
	Node * tnode = (Node*)malloc(sizeof(*tnode));
	//tnode->address = str;
	tnode->chan = 5;
	return  tnode;
}*/


/*int main(){

	return 0;
}*/
