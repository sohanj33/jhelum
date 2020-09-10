#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_transform(char type[])
{
	if(!strcmp(type,"CreditReport"))
	{
		printf("\nNeed transforamtion\n");
	}
	else
	{
		printf("\nNo transformation needed\n");
	}
	
}
