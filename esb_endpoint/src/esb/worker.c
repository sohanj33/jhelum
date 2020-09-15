#include <stdio.h>
#include <unistd.h>
#include "esb.h"
#include "bmd_parser.h"
#include <mysql.h>
#include "database.h"
#include <stdlib.h>
#include <string.h>


int fetch_new_request_from_db(int id)
{
    /** 
     * TODO: query the DB for this, and populate the 
     * request pointer with the requests.
     */
	printf("Checking for new requests in esb_requests table.\n");
	if(check_new_request(id)>=1)
	{
		printf("\nFound a new request\n");
		return 1; // 1 => OK, -1 => Errors
	}
	else
	{
		printf("\nno new requests found\n");
		return 0;
	}
}

/**
 * TODO: Implement the proper logic as per ESB specs.
 */
void *poll_database_for_new_requets(void *vargp)
{
    // Step 1: Open a DB connection
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

    int i = 0;
    while (i < 99)
    {
        i++;
        /**
         * Step 2: Query the esb_requests table to see if there
         * are any newly received BMD requets.
         */
        //Execute
	
        int ID;
        char SENDER[50];
        char DEST[50];
        char MTYPE[50];	
	       
        /*Query to see rows with status = available*/
        
        mysql_query(conn, "SELECT id, sender_id, dest_id, message_type FROM esb_request WHERE status = 'available' ORDER BY id LIMIT 1");
        res = mysql_store_result(conn);
        int columns = mysql_num_fields(res);
	 
	 printf("Entries in the table esb_request with status = available :\n");
	 while((row = mysql_fetch_row(res)))
	 {
	   for (int i = 0; i < 4; i++)
	   {
	     printf("%s ", row[i] ? row[i] : "NULL");
	     switch(i){
			case 0:     
		     		ID = atoi(row[i]);
		     		break;
		     	
			case 1:     
		     		strcpy(SENDER, row[i]);
		     		break;
		     		
			case 2:     
		     		strcpy(DEST, row[i]);
		     		break;
		     		
			case 3:     
		     		strcpy(MTYPE,row[i]);
		     		break;
     		}
	   }
	   printf("\n");
	 }
 		
	mysql_free_result(res);
	

            BMD *req;
            /**
         * Step 3:
         */
            if (fetch_new_request_from_db(ID))
            {
                /**
              * Found a new request, so we will now process it.
              * See the ESB specs to find out what needs to be done
              * in this step. Basically, you will be doing:
              * 1. Find if there is any transformation to be applied to
              *    the payload before transporting it to destination.
              * 2. If needed, transform the request.
              * 3. Transport the transformed data to destination.
              * 4. Update the status of the request in esb_requests table
              *    to mark it as done (or error) depending on the outcomes
              *    of this step.
              * 5. Cleanup
              */
               printf("\nApplying transformation and transporting steps.\n");
              /*Step 1: Change status from available to taken*/
              
		change_available_to_taken(ID);
              
              /*Step 2: Transformation steps: */
             
		/*Find the route_id for which transformation is to applied*/
		int route_id = get_route_id(SENDER, DEST, MTYPE);
		if(route_id==NULL)
		{
			change_status_to_error(ID);
			return;
		}
		
		/*Get the config_key to check for transformation*/
		char transform_key[50];
		get_transform_key(route_id, transform_key);
		
		if(transform_key==NULL)
		{
			change_status_to_error(ID);
			return;
		}
		
		printf("\ntransform key: %s\n",transform_key);
		
		/* Check if transformation is required */
		
		/* Get for transport service value */
		char transport_value[50];
		get_transport_value(route_id, transport_value);
		
		if(transport_value==NULL)
		{
			change_status_to_error(ID);
			return;
		}
		
		printf("\ntransport value: %s\n",transport_value);
		
		/* Get for transport service key */
		char transport_key[50];
		check_transform(transform_key,route_id,transport_key, transport_value, SENDER);
		
		if(transport_key==NULL)
		{
			change_status_to_error(ID);
			return;
		}
		
		printf("\ntransport key: %s\n",transport_key);
		
             /* Step 3: Transportation steps: */
		
		/* Check & Apply the transport service */
                int transport_status = Apply_transport_service(transport_key, transport_value);
                if(transport_status==0)
		{
			change_status_to_error(ID);
			return;
		}
                
            /* Step 4: Check and update the status */
            	
            	/*Change status taken to done*/
            	
            	change_taken_to_done(ID);
               
            
            /* Step 5: Cleanup */
             //To be implemented
               
            }
        /**
         * Sleep for polling interval duration, say, 5 second.
         * DO NOT hard code it here!
         */
        printf("Sleeping for 5 seconds.\n");
        sleep(5);
    }
}

