#include<stdio.h>
#include<stdlib.h>

void xml2json(char Pay[])
{
	char filename[] = "Payload.json";
        FILE *file;
    	file = fopen(filename,"w");
    	
    	if(file == NULL) 
    	{
        	printf("file opening filed");
        	exit(0);
    	}
    	
    	/* Writes into json file */
    	fprintf(file,"{\n \"Payload\":\"%s\"\n}",Pay);
    	
    	printf("\nPayload json File created\n");
   	 /* Closes file */
    	fclose(file);
    	/* returns json filename */
    	//return strdup(filename);
}
