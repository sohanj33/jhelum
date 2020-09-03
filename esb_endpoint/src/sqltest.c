/* gcc -o EXEName $(mysql_config --cflags) sqltest.c $(mysql_config --libs) */
/* ./EXEName */


#include <mysql.h>
#include <stdio.h>
#include <string.h>

void sqlcon() {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	
	char *server = "localhost";
	char *user = "splunk_user";
	char *password = "password"; /* set me first */
	char *database = "esb_db";

	int8_t Message_ID = 1;
	int8_t sender_id[] = "1100";
	int8_t dest_id[] = "2100";
  	int8_t Message_Type[] = "1message";
 	int8_t reference_id[] = "1100200";
  	int8_t message_id[] = "11010";
  	int8_t received_on[] = "2017-02-18";
  	int8_t data_location[] = "1mumbai";
  	int8_t status[] = "negative1";
  	int8_t status_details[] = "1inprocess";
  	char query[1000];
	
	
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
	 
	 while(row = mysql_fetch_row(res))
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
	 
	 sprintf(query, "INSERT INTO esb_request(id, sender_id, dest_id, message_type, reference_id, message_id, received_on, data_location, status, status_details) VALUES (%d, '%s','%s', '%s','%s', '%s','%s', '%s','%s', '%s')",Message_ID, sender_id, dest_id, Message_Type, reference_id, message_id, received_on, data_location, status, status_details);
	 
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
		
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
	 while(row = mysql_fetch_row(res))
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
