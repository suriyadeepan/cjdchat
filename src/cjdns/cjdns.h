#ifndef CJDNS_H
#define CJDNS_H

#include "../cjdchat.h"
#include "vector"
#include "string"

using namespace std;

int cjdns_getPeers(vector<string> *);
void *cjdns_trackPeers(void *);

#endif
