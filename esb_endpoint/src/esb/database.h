#ifndef DATABASE 
#define DATABASE 

#define INSERT_IN_ESB_REQUEST  "INSERT INTO esb_request(sender_id,dest_id,message_type,reference_id,message_id,received_on,status) VALUES ('%s','%s','%s','%s','%s','%s','%s')"
#define SELECT_ACTIVE_ROUTE "SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'  AND is_active=b'1'"
#define SELECT_TRANSPORT_CONFIG "SELECT * FROM transport_config WHERE route_id='%d'"
#define SELECT_TRANSFORM_CONFIG "SELECT * FROM transform_config WHERE route_id='%d'"
#define CHECK_NEW_REQUEST "SELECT * FROM esb_request WHERE status = 'available' LIMIT 1" 




#define server "localhost"
#define user "root"
#define password "Akshay12#$"
#define database "esb_db"
#define port 3306

int insert_in_esb_request(BMD *bmd);
int select_active_route(const unsigned char *Sender, const unsigned char *Destination, const unsigned char *MessageType);
int select_transport_config(int route_id);
int select_transform_config(int route_id);

#endif