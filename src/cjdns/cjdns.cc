#include "stdio.h"


int main(){


	FILE *fp;
	int status;
	char path[100];


	fp = popen("$HOME/install/cjdns/tools/dumptable | grep v16", "r");
	if (fp == NULL)
		/* Handle error */;


	while (fgets(path, 100, fp) != NULL){
			printf("%s\n", path);
	}


	status = pclose(fp);
	if (status == -1) {
		/* Error reported by pclose() */
	} else {
		/* Use macros described under wait() to inspect `status' in order
			 to determine success/failure of command executed by popen() */
	}

}
