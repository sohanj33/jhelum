#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_transform(char type[], int route_id, char* transport_key, char* transport_value, char* SENDER)
{
	if((!strcmp(type,"Json_transform"))&&(!strcmp(transport_value,"HTTP")))
	{
		printf("\nHTTP_Json transformation\n");
		HTTP_Json_transform(route_id, transport_key, SENDER);
	}
	else if((!strcmp(type,"Json_transform"))&&(!strcmp(transport_value,"email")))
	{	
		printf("\nEmail_Json transformation\n");
		get_emailID(route_id, transport_key);
	}
	else
	{
		printf("\nNo transformation needed\n");
		
	}
	
}

void HTTP_Json_transform(int route_id, char* transport_key, char *SENDER)
{
	char temp[100];
	char* filename;
	strcpy(filename, SENDER);
	strcat(filename, "Payload.json");
	FILE *fp = fopen(filename, "r");
	fp = fopen(filename, "r");
   	
   	if (fp == NULL)
      		  return;
	
	int i=0;
	char c = fgetc(fp); 
    	while (c != EOF)
    	{ 
	     temp[i++] = c;
	     c = fgetc(fp);
        }
	temp[i]='\0';
	
	char payload[strlen(temp)];
	int k=0;
	for(int i=0;i<strlen(temp);i++)
	{
		if(temp[i]==':')
		{
			for(int j=i+2;j<strlen(temp);j++)
			{
				if(temp[j]=='"')
					break;
				payload[k++] = temp[j];
			}
			break;		
		}
	}
	
	printf("\nPayload:\t%s\n",payload);
	
	add_payload(payload, route_id, transport_key);
	
}
