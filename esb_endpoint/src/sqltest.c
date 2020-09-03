/* gcc -o EXEName $(mysql_config --cflags) sqltest.c $(mysql_config --libs) */
/* ./EXEName */


#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <bmd_parser.h>
void sqlcon(BMD *bmd) {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	
	char *server = "localhost";
	char *user = "splunk_user";
	char *password = "password"; /* set me first */
	char *database = "esb_db";

	 int8_t ID = 1;
	// int8_t sender_id[] = "1100";
	// int8_t dest_id[] = "2100";
  	// int8_t Message_Type[] = "1message";
 	// int8_t reference_id[] = "1100200";
  	// int8_t message_id[] = "11010";
  	 int8_t received_temp[100]; //= "2020-08-12 05:18:00+0000";
  	 int8_t received_on[100];
  	 strcpy(received_temp,bmd->bmd_envelope->CreationDateTime);
  	// int8_t data_location[] = "1mumbai";
  	// int8_t status[] = "negative1";
  	// int8_t status_details[] = "1inprocess";
  	// char query[1000];
  	
  	/*Changing DateTime format*/
  	int n = strlen(received_temp);
  	int j=0;
  	for(int i=0;i<=n; i++)
  	{
  		received_on[j] = received_temp[i];
  		if(received_on[i]=='T')		//test for character
		{
			received_on[i] = ' '; // write next character back to current position
		}
		if(i==n-3)
		{
			char ch = ':';
		  	strncat(received_on, &ch, 1); 
		  	j++;			
		}
		j++;
	}
  	
	
	
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
	 
	 while( (row = mysql_fetch_row(res)))
	 {
	     printf("%s ", row[0]);
	 }
	 
	 printf("\n");
	  
	 
	 mysql_free_result(res);
	 
	 /*sql query to delete in table*/
	 
	if (mysql_query(conn, "DELETE FROM esb_request WHERE ID = '1'")) //to maintain non duplicay temporarily
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
		
	}
	 
	 res = mysql_use_result(conn);
	 
	 /*free the result*/	  
	 
	 mysql_free_result(res);
	 
	 /*sql query to insert in table*/
	char *status="availble";
	char query[5000];
     printf("INSERT INTO esb_request(sender_id, dest_id, message_type, reference_id, message_id, received_on,status) VALUES (%s,%s,%s,%s,%s,%s,%s)\n\n", bmd->bmd_envelope->Sender ,bmd->bmd_envelope->Destination,bmd->bmd_envelope->MessageType,bmd->bmd_envelope->ReferenceID,bmd->bmd_envelope->MessageID,bmd->bmd_envelope->CreationDateTime,status);
     
	 sprintf(query, "INSERT INTO esb_request(id, sender_id, dest_id, message_type, reference_id, message_id, received_on, status) VALUES (%d, '%s','%s', '%s','%s', '%s','%s','%s')", ID, bmd->bmd_envelope->Sender, bmd->bmd_envelope->Destination, bmd->bmd_envelope->MessageType, bmd->bmd_envelope->ReferenceID, bmd->bmd_envelope->MessageID, received_on, status);
	 
	 
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query.Error: %s\n", mysql_error(conn));
		
	}
	 
	 res = mysql_use_result(conn);
	 
	 /*free the result*/	  
	 
	 mysql_free_result(res);
	 
	//sprintf(query, "INSERT INTO esb_request(id, sender_id, dest_id, message_type, reference_id, message_id, received_on, data_location, status, status_details) VALUES ('%s', '%s','%s', '%s','%s', '%s','%s', '%s','%s', '%s')",Message_ID, sender_id, dest_id, Message_Type, reference_id, message_id, received_on, data_location, status, status_details);
	 
	// /*sql query to insert in table*/
	 
	// if (mysql_query(conn, "INSERT INTO esb_request(id, sender_id, dest_id, message_type, reference_id, message_id, received_on, data_location, status, status_details) VALUES(1,'100','200','message','100200','1100','2015-02-18','mumbai','negative','inprocess')"))
	// {
	//   printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	//   return 0;
	// }
	 
	// res = mysql_use_result(conn);
	 
	 /*free the result*/	  
	 
	// mysql_free_result(res);
	 
	 /* send SQL query to display values */
	 
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
	 while((row = mysql_fetch_row(res)))
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
