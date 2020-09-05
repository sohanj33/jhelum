/* gcc -o EXEName $(mysql_config --cflags) sqltest.c $(mysql_config --libs) */
/* ./EXEName */

#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <bmd_parser.h>
#define SELECT_ACTIVE_ROUTE "SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'  and is_active=1"
#define SELECT_TRANSPORT_CONFIG "SELECT * FROM transport_config WHERE route_id='%d"
#define SELECT_TRANSFORM_CONFIG "SELECT * FROM transform_config WHERE route_id='%d"
char *server = "localhost";
char *user = "root";
char *password = "Akshay12#$"; /* set me first */
char *database = "esb_db";
int port = 3306;		  /*port number*/
char *unix_socket = NULL; /*unix socket*/

void sqlcon(BMD *bmd)
{

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/* Execute SQL query to fetch all table names.*/
	if (mysql_query(conn, "show tables"))
	{
		printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);

	/* Output table name */
	// printf("MySQL Tables in mydb database:\n");
	//while ((row = mysql_fetch_row(res)) != NULL)
	//printf("%s \n", row[0]);

	/* free results */
	mysql_free_result(res);

	/*sql query for columns in table*/

	if (mysql_query(conn, "DESCRIBE esb_request"))
	{
		printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);

	/*output column names*/

	while ((row = mysql_fetch_row(res)))
	{
		printf("%s ", row[0]);
	}

	printf("\n");

	mysql_free_result(res);

	/*sql query to delete in table*/

	if (mysql_query(conn, "DELETE FROM esb_request WHERE data_location = '1mumbai'")) //to maintain non duplicay temporarily
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);

	/*free the result*/

	mysql_free_result(res);

	/*sql query to insert in table*/
	char *status = "availble";
	unsigned char *date;
	char query[5000];
	date = bmd->bmd_envelope->CreationDateTime;
	date[10] = ' ';
	sprintf(query, "INSERT INTO esb_request(sender_id,dest_id,message_type,reference_id,message_id,received_on,status)");
	sprintf(query, "%s\nVALUES ('%s','%s','%s','%s','%s','%s','%s');",
			query,
			bmd->bmd_envelope->Sender,
			bmd->bmd_envelope->Destination,
			bmd->bmd_envelope->MessageType,
			bmd->bmd_envelope->ReferenceID,
			bmd->bmd_envelope->MessageID,
			date, status);
	printf("\n\n\n\n\n%s \n\n\n\n\n", query);

	if (mysql_query(conn, query))
	{
		printf("Failed to execute query.Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);

	/*free the result*/

	mysql_free_result(res);

	if (mysql_query(conn, "select * from esb_request"))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	if (res == NULL)
	{
		printf("Failed");
	}

	/*display values in the table*/

	int columns = mysql_num_fields(res);
	int i = 0;

	printf("Entries in the table esb_request:\n");
	while ((row = mysql_fetch_row(res)))
	{
		for (i = 0; i < columns; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	mysql_free_result(res);
	mysql_close(conn);
}
//Returns route_id if an active route exists for a given sender , destination and message type
int select_active_route(unsigned char *Sender, unsigned char *Destination, unsigned char *MessageType)
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
			success = row[0];
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

