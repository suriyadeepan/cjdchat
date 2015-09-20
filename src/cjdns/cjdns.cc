#include "cjdns.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "dirent.h"
#include "sys/types.h"

#include "vector"
#include "string"

#include "../model/model.h"

using namespace std;

//extern Node **model;
//extern int peer_count;
extern vector<string> ip_list;

void *cjdns_trackPeers(void *){
	
	while(1){
		sleep(10);
		ip_list.clear();
		cjdns_getPeers(&ip_list);
		model_peerUpdate(&ip_list);
	}

}


/*pid_t proc_find(const char* name) 
{
    DIR* dir;
    struct dirent* ent;
    char* endptr;
    char buf[512];

    if (!(dir = opendir("/proc"))) {
        perror("can't open /proc");
        return -1;
    }

    while((ent = readdir(dir)) != NULL) {
        long lpid = strtol(ent->d_name, &endptr, 10);
        if (*endptr != '\0') {
            continue;
        }

        snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
        FILE* fp = fopen(buf, "r");

        if (fp) {
            if (fgets(buf, sizeof(buf), fp) != NULL) {
                char* first = strtok(buf, " ");
                if (!strcmp(first, name)) {
                    fclose(fp);
                    closedir(dir);
                    return (pid_t)lpid;
                }
            }
            fclose(fp);
        }

    }

    closedir(dir);
    return -1;
}*/


int cjdns_getPeers(vector<string> *ip_list){

	FILE *fp;
	char path[100];

	// check if cjdns is running
	/*if(proc_find("cjdroute") == -1)
		return -1;*/

	fp = popen("/home/suriya/install/cjdns/tools/loop_dumptable","r");
	
	if (fp == NULL)
		/* Handle error */;


	while (fgets(path, 100, fp) != NULL){
			strtok(path,"\n");
			ip_list->push_back(path);
	}
	
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
