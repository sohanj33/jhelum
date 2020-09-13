#include <stdio.h>
#include <stdlib.h>
#include <string.h>

<<<<<<< HEAD
=======
void check_transform(char type[], int route_id)
{
	if(!strcmp(type,"json"))
	{
		printf("\nNeed transformation\n");
		no_transform(route_id);
		//add route_id
	}
	else
	{
		printf("\nNo transformation needed\n");
		
	}
	
}
>>>>>>> 387e8cc560d9d7b4e7ab7a9de91a0f06ffa7fc9e

void no_transform(int route_id)
{
	char temp[100];
	FILE *fp = fopen("Payload.json", "r");
	
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
	for(i=0;i<strlen(temp);i++)
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
	
<<<<<<< HEAD
	//add_payload(payload);
	
}






void check_transform(char type[])
{
	if(!strcmp(type,"json"))
	{
		printf("\nNeed transformation\n");
		no_transform();
	}
	else
	{
		printf("\nNo transformation needed\n");
		
	}
=======
	add_payload(payload, route_id);
>>>>>>> 387e8cc560d9d7b4e7ab7a9de91a0f06ffa7fc9e
	
}
