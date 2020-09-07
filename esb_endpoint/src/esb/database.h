#define INSERT_IN_ESB_REQUEST  "INSERT INTO esb_request(sender_id,dest_id,message_type,reference_id,message_id,received_on,status) VALUES ('%s','%s','%s','%s','%s','%s','%s')"
#define SELECT_ACTIVE_ROUTE "SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'  AND is_active=b'1'"
#define SELECT_TRANSPORT_CONFIG "SELECT * FROM transport_config WHERE route_id='%d'"
#define SELECT_TRANSFORM_CONFIG "SELECT * FROM transform_config WHERE route_id='%d'"


char *server = "localhost";
char *user = "root";
char *password = "Akshay12#$"; /* set me first */
char *database = "esb_db";
int port = 3306;		  /*port number*/
char *unix_socket; /*unix socket*/

int insert_in_esb_request(BMD *bmd);
int select_active_route(const unsigned char *Sender, const unsigned char *Destination, const unsigned char *MessageType);
int select_transport_config(int route_id);
int select_transform_config(int route_id);