#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Apply_transport_service(char URL[], char transport_service[])
{
	if(!strcmp(transport_service,"HTTP"))
	{
		printf("\nHTTP service applied\n");
		send_http_request(URL);
	}
	else
	{
		printf("\nNo service found\n");
	}
	
}

