#define START_TAG 1 //value acoording to return type of xmlTextReaderNodeType
#define END_TAG 15
unsigned char ENVELOPE[] = "ENVELOPE";
unsigned char MessageID[] = "MessageID";
unsigned char MessageType[] = "MessageType";
unsigned char Sender[] = "Sender";
unsigned char Destination[] = "Destination";
unsigned char CreationDateTime[] = "CreationDateTime";
unsigned char Signature[] = "Signature";
unsigned char UserProperties[] = "UserProperties";
unsigned char ReferenceID[] = "ReferenceID";

typedef struct
{
  const unsigned char *key;
  void *value;
} pair;

typedef struct
{
  const unsigned char *MessageID;
  const unsigned char *MessageType;
  const unsigned char *Sender;
  const unsigned char *Destination;
  const unsigned char *CreationDateTime;
  const unsigned char *Signature;
  pair *UserProperties[50];
  const unsigned char *ReferenceID;

} envelope;

typedef struct
{
  const unsigned char *data;
} payload;

int processXML(char *);
envelope *extract_envelop(char *bmd_xml);
payload *extract_payload(char *bmd_xml);