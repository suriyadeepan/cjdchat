#ifndef MODEL_H
#define MODEL_H

#include "../cjdchat.h" //--> include all the ENUM, global constants in src/cjdchat.h
#include "vector"
#include "string"

using namespace std;

typedef struct _Node{

	char address[40];
	char nick[10];
	char chan[100];

} Node;


int model_init(Node **, vector<string> *);
void model_echo(Node **,int);
Node* model_newNode();

#endif
