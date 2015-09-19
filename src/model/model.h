#ifndef MODEL_H
#define MODEL_H

#include "../cjdchat.h" //--> include all the ENUM, global constants in src/cjdchat.h
#include "vector"
#include "string"

using namespace std;

typedef struct _Node{

	string address;
	char nick[40];
	int chan[10];

} Node;


int model_init(Node **, vector<string> *);
Node* model_newNode(string);

#endif
