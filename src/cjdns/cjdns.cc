#include "stdio.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){


	FILE *fp;
	int status;
	char path[100];

	vector<string> ip_list;

	fp = popen("./loop_dumptable","r");
	//fp = popen("$HOME/install/cjdns/tools/dumptable");
	if (fp == NULL)
		/* Handle error */;


	while (fgets(path, 100, fp) != NULL){
			//printf("%s", path);
			ip_list.push_back(path);
	}


	status = pclose(fp);
	if (status == -1) {
		/* Error reported by pclose() */
	} else {
		/* Use macros described under wait() to inspect `status' in order
			 to determine success/failure of command executed by popen() */
	}


	printf("-----------------");
	for(int i=0;i<ip_list.size();i++)
		printf("\n%s",ip_list[i].c_str());
	printf("-----------------");

	return 0;

}
