#ifndef CNTL_H
#define CNTL_H

#include "../cjdchat.h"

/* -- Moved to ../cjdchat.h -- */
//extern enum {JOIN,MSG,PART,PARTALL,IGNORE,QUIT,HELP};
/*
 *  Message format:
		1. "blah blah" -> normal msg (broadcasted to all)
		2. "/msg nick ksjdf" -> private msg, unicasted to ipv6(nick)
		3. "/part chan" -> leave channel
		4. "/partall" -> leave all channels except #general
		5. "/join chan" -> join chan
		6. "/quit" -> exit

 */

//int cntl_identify(char *);
int cntl_splitter(char* ,char* );

#endif
