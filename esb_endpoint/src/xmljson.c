#include<stdio.h>
#include <stdlib.h>

void xml2json(char Pay[])
{
	char filename[] = "/home/utkarsh/Documents/jhelum-master/esb_endpoint/bmd_files/Payload.json";
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
    	
    	/*File size validation*/
    	 FILE *fp;
   	 int size = 0;
 
   	 fp = fopen(filename, "r");
   	 if (fp == NULL)
      		  printf("\nFile unable to open ");
   	 else 
     	   printf("\nFile opened ");
   	 fseek(fp, 0, 2);    /* file pointer at the end of file */
   	 size = ftell(fp);   /* take a position of file pointer un size variable */
   	
   	/*Check if Filesize is larger than 5MB*/
   	if(size>5000000)
   		printf("\nFile size larger than 5MB not allowed!\n");
   	  
   	 fclose(fp); 
        
    	/* returns json filename */
    	return strdup(filename);
}
