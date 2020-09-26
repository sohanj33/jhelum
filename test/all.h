#include <stdio.h>
#include <libxml2/libxml/xmlreader.h>
#include <curl/curl.h>
//#include "bmd_parser.h"
#include <ctype.h>
#include <string.h>
#include "../esb/xmljson.c"
#include "../bmdParse/bmd_parser.c"
#include "../adapter/http.c"
#include "../route/transport.c"
#include "../route/transform.c"
#include "../adapter/email.c"
//#include "../adapter/sftp.c"
#include "../esb/esb.c"
#include "../database/database.c"
//#ifdef LIBXML_READER_ENABLED


//return 1 if string is a valid GUID
int check_if_string_is_guid(const xmlChar * value); 

//Returns text data present between Start Tag and End Tag of XML.
static
const xmlChar * get_node_data(xmlTextReaderPtr reader); 
/*
 Stores text in respective bmd field.
 */
static void
process_nodes(xmlTextReaderPtr reader, envelope * bmd_envelope, payload * bmd_payload); 

//Parses the entire XML
static void
streamFile(const char * bmd_file_path, envelope * bmd_envelope, payload * bmd_payload); 

static envelope * get_envelope_struct(); 

static payload * get_payload_struct(); 

BMD * process_xml(char * bmd_file_path); 
int get_filesize(char filename[]); 

char * get_filecontents(char filename[]); 

/* This function is defined for testing */
char * xmltojson(char Pay[]); 

int Apply_transport_service(char URL[], char transport_service[], char SENDER[], char transform_key[]); 

int select_active_route(const unsigned char * Sender, const unsigned char * Destination, const unsigned char * MessageType);
