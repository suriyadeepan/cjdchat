#include "model.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

extern int peer_count;
extern Node** model;

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
		strcpy(tnode->nick , "nameless");
		strcpy(tnode->chan , "nameless");
		model[i] = tnode;
	}

}


void model_peerUpdate(vector<string> *ip_list){

	int initial_peer_count = peer_count;

	for(int i=0;i<ip_list->size();i++)// if peer not present in model, add to model
		if( model_searchPeer( (*ip_list)[i].c_str() ) == -1 ){

			Node * tnode = (Node*)malloc(sizeof(*tnode));
			strcpy(tnode->address , (*ip_list)[i].c_str());
			strcpy(tnode->nick , "nameless");
			strcpy(tnode->chan , "nameless");
			peer_count++;
		}
	if(peer_count != initial_peer_count){
		printf("\n$ Internal Message : Peer Status changed; Model update");
		model_echo(model,peer_count);
	}
	

}

void model_echo(Node* model[],int peer_count){

	printf("\n---------------");
	for(int i=0;i< peer_count;i++)
		printf("\n%d.%s",i,model[i]->address);//, model[i]->nick,model[i]->chan);
	printf("\n---------------");
}

void model_updateNick(Node* model[],char *nick){
	strcpy((*model)[0].nick,nick);
}

void model_addNick(char *ip, char *nick){

	for(int i=0;i< peer_count;i++)
		if(strcmp(ip,model[i]->address) == 0)
			strcpy(model[i]->nick,nick);
}

void model_ipToNick(char *ip, char *nick){
	
	for(int i=0;i< peer_count;i++)
		if(strcmp(ip,model[i]->address) == 0)
			strcpy(nick,model[i]->nick);

}

int model_searchPeer(const char *ip){
	
	for(int i=0;i< peer_count;i++)
		if(strcmp(ip,model[i]->address) == 0)
			return 0;

	return -1;
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
