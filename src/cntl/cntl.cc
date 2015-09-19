#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>

#include "cntl.h"


int cntl_identify(char input_command[]){

	if(!strcmp(input_command,"join"))
		return JOIN;
	else if(!strcmp(input_command,"msg"))	
		return MSG;
	else if(!strcmp(input_command,"part"))
		return PART;
	else if(!strcmp(input_command,"partall"))
		return PARTALL;
	else if(!strcmp(input_command,"ignore"))
		return IGNORE;
	else if (!strcmp(input_command,"quit"))
		return QUIT;
	else if(!strcmp(input_command,"help"))
		return HELP;


}




int cntl_splitter(char* input_string,char* output_message){

	char command[10]={'\0'},message[50]={'\0'};
	int n=strlen(input_string),result_command;

	int i,j,k;

	/*if(input_string[0] != '/')
		printf("Invalid form");*/
	i=1;
	while(input_string[i]!=' ' && input_string[i] != '\0'){
		command[i-1]=input_string[i];
		i++;
	}
	while(input_string[i]==' ')
		i++;

	for(k=0;input_string[i]!='\0';i++,k++){
		message[k]=input_string[i];
	}

	strcpy(output_message,message);
	result_command = cntl_identify(command);
	return result_command;
}




/*int main(){
	int result;
	char input[100],output[100]={'\0'};
	scanf("%[^\n]s",input);
	result=cntl_splitter(input,output);
	printf("%d and %s",result,output); 

	return 0;
}*/
