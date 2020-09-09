#include <stdio.h>
#include <unistd.h>
#include "esb.h"
#include "bmd_parser.h"
#include <mysql.h>
#include "database.h"
int fetch_new_request_from_db(BMD *request)
{
    /** 
     * TODO: query the DB for this, and populate the 
     * request pointer with the requests.
     */
    printf("Checking for new requests in esb_requests table.\n");
    return 1; // 1 => OK, -1 => Errors
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
        int count = 0;
        if (mysql_query(conn, "SELECT COUNT(*) FROM esb_request WHERE status='available'"))
        {
            printf("Failed to execute query.Error: %s\n", mysql_error(conn));
        }
        res = mysql_use_result(conn);
        if ((row = mysql_fetch_row(res)) != NULL)
        {
            count = atoi(row[0]);
        }
        mysql_free_result(res);

        if (count > 0)
        {
            BMD req;
            /**
         * Step 3:
         */
            if (fetch_new_request_from_db(&req))
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
                printf("Applying transformation and transporting steps.\n");
            }
        }
        /**
         * Sleep for polling interval duration, say, 5 second.
         * DO NOT hard code it here!
         */
        printf("Sleeping for 5 seconds.\n");
        sleep(5);
    }
}