#include "cjdns.h"
#include "stdio.h"

using namespace std;

int cjdns_getPeers(vector<string> *ip_list){

	FILE *fp;
	char path[100];

	fp = popen("/home/suriya/install/cjdns/tools/loop_dumptable","r");
	
	if (fp == NULL)
		/* Handle error */;


	while (fgets(path, 100, fp) != NULL)
			ip_list->push_back(path);
	
	pclose(fp);
	/*printf("-----------------");
	for(int i=0;i<ip_list->size();i++)
		printf("\n%s",(*ip_list)[i].c_str());
	printf("-----------------\n");
	*/

	return ip_list->size();
}

/*int main(){

	vector<string> ip_list;
	cjdns_getPeers(&ip_list);

	return 0;

}*/
