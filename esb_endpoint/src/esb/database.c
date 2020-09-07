/* gcc -o EXEName $(mysql_config --cflags) sqltest.c $(mysql_config --libs) */
/* ./EXEName */

#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmd_parser.h"
#include "database.h"

int insert_in_esb_request(BMD *bmd)
{
    int success =1; //1=>success , -ve for errors
	
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
		success=-1;
		return success;
	}


	/*sql query to insert in table*/
	char *status = "availble";
	char query[5000];
	sprintf(query,INSERT_IN_ESB_REQUEST,
			bmd->bmd_envelope->Sender,
			bmd->bmd_envelope->Destination,
			bmd->bmd_envelope->MessageType,
			bmd->bmd_envelope->ReferenceID,
			bmd->bmd_envelope->MessageID,
			bmd->bmd_envelope->CreationDateTime
			,status);

	printf("\n\n%s\n\n", query);

	if (mysql_query(conn, query))
	{
		printf("Failed to execute query.Error: %s\n", mysql_error(conn));
		success=-1;
		return success;
	}

	res = mysql_use_result(conn);

	/*free the result*/

	mysql_free_result(res);
	mysql_close(conn);
	return success;
}
//Returns route_id if an active route exists for a given sender , destination and message type
int select_active_route(const unsigned char *Sender, const unsigned char *Destination,const unsigned char *MessageType)
{
	int success = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/* Execute SQL query to fetch all table names.*/
	sprintf(query, SELECT_ACTIVE_ROUTE, Sender, Destination, MessageType);
	if (mysql_query(conn, query))
	{
		printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);
	if (res->row_count == 1)
	{
		while ((row = mysql_fetch_row(res)) != NULL)
			success = atoi(row[0]);
	}
	else
	{
		success = -1;
	}

	/* Output table name */
	// printf("MySQL Tables in mydb database:\n");
	//while ((row = mysql_fetch_row(res)) != NULL)
	//printf("%s \n", row[0]);

	/* free results */
	mysql_free_result(res);
	return success;
}

int select_transport_config(int route_id)
{
	int success = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/* Execute SQL query to fetch all table names.*/
	sprintf(query, SELECT_TRANSPORT_CONFIG,route_id);
	if (mysql_query(conn, query))
	{
		printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);
	if (res->row_count >= 1)
	{
		success=1;
	}
	else
	{
		success = -1;
	}

	/* free results */
	mysql_free_result(res);
	return success;
}

int select_transform_config(int route_id)
{
	int success = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	
	sprintf(query, SELECT_TRANSFORM_CONFIG,route_id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);
	if (res->row_count >= 1)
	{
		success=1;
	}
	else
	{
		success =-1;
	}

	/* free results */
	mysql_free_result(res);
	return success;
}
