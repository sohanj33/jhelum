/**
 * section: xmlReader
 * synopsis: Parse and validate an XML file with an xmlReader
 * purpose: Demonstrate the use of xmlReaderForFile() to parse an XML file
 *          validating the content in the process and activating options
 *          like entities substitution, and DTD attributes defaulting.
 *          (Note that the XMLReader functions require libxml2 version later
 *          than 2.6.)
 * usage: reader2 <valid_xml_filename>
 * test: reader2 test2.xml > reader1.tmp && diff reader1.tmp $(srcdir)/reader1.res
 * author: Daniel Veillard
 * copy: see Copyright for the status of this software.
 */

#include <stdio.h>
#include <libxml/xmlreader.h>
#include <bmd_parser.h>
#include <ctype.h>
#include <string.h>
#ifdef LIBXML_READER_ENABLED

unsigned char ENVELOPE[] = "Envelop";
unsigned char Payload[] = "Payload";
unsigned char MessageID[] = "MessageID";
unsigned char MessageType[] = "MessageType";
unsigned char Sender[] = "Sender";
unsigned char Destination[] = "Destination";
unsigned char CreationDateTime[] = "CreationDateTime";
unsigned char Signature[] = "Signature";
unsigned char UserProperties[] = "UserProperties";
unsigned char ReferenceID[] = "ReferenceID";


//return 1 if string is a valid GUID
static int check_if_string_is_guid(const xmlChar *value)
{
    int len = xmlStrlen(value);

    if (len != 36)
        return 0;

    int hyphens[4] = {9, 14, 19, 24};

    for (int i = 0, counter = 0; i < 36; i++)
    {
        char var = value[i];
        if (i == hyphens[counter] - 1) // Check if a hyphen is expected here.
        {
            //We need a hyphen here.
            if (var != '-')
            {
                return 0; //The character is not a hyphen.
            }
            else
            {
                counter++; // Move on to the next expected hyphen position.
            }
        }
        else
        {
            // The character here should be a simple xdigit
            if (isxdigit(var) == 0)
            {
                return 0; //The current character is not a hyphen.
            }
        }
    }
    return 1;
}

static void
process_nodes(xmlTextReaderPtr reader, envelope *bmd_envelope, payload *bmd_payload)
{
    if (xmlTextReaderNodeType(reader) != START_TAG)
        return;

    const xmlChar *name, *value;

    name = xmlTextReaderConstName(reader);

    value = xmlTextReaderConstValue(reader);

    int ret = 0;
    // printf("%d %d %s %d %d\n",
    //        xmlTextReaderDepth(reader),
    //        xmlTextReaderNodeType(reader),
    //        name,
    //        xmlTextReaderIsEmptyElement(reader),
    //        xmlTextReaderHasValue(reader));

    if (xmlStrcmp(MessageID, name) == 0)
    {

        ret = xmlTextReaderRead(reader);

        if (ret == 1)
            value = xmlTextReaderConstValue(reader);
        else
        {
            fprintf(stderr, "%s is not valid \n", name);
            return;
        }

        if (value != NULL)
        {
            int is_guid = check_if_string_is_guid(value);
            if (is_guid == 0)
            {
                fprintf(stderr, "%s is not a valid GUID \n", name);
                return;
            }
        }

        bmd_envelope->MessageID = xmlStrdup(value);
        printf("Envelope Message ID is valid value: %s \n", bmd_envelope->MessageID);
    }

    if (xmlStrcmp(MessageType, name) == 0)
    {

        ret = xmlTextReaderRead(reader);
        if (ret == 1)
            value = xmlTextReaderConstValue(reader);
        else
        {
            fprintf(stderr, "%s is not valid \n", name);
            return;
        }

        bmd_envelope->MessageType = xmlStrdup(value);
        printf("Message Type %s \n", bmd_envelope->MessageType);
    }

    if (xmlStrcmp(Sender, name) == 0)
    {

        ret = xmlTextReaderRead(reader);
        if (ret == 1)
            value = xmlTextReaderConstValue(reader);
        else
        {
            fprintf(stderr, "%s is not valid \n", name);
            return;
        }

        if (value != NULL)
        {
            int is_guid = check_if_string_is_guid(value);
            if (is_guid == 0)
            {
                fprintf(stderr, "%s is not a valid GUID \n", name);
                return;
            }
        }

        bmd_envelope->Sender = xmlStrdup(value);
        printf("Envelope Sender is valid  %s \n", bmd_envelope->Sender);
    }

    if (xmlStrcmp(Destination, name) == 0)
    {

        ret = xmlTextReaderRead(reader);
        if (ret == 1)
            value = xmlTextReaderConstValue(reader);
        else
        {
            fprintf(stderr, "%s is not valid \n", name);
            return;
        }

        if (value != NULL)
        {
            int is_guid = check_if_string_is_guid(value);
            if (is_guid == 0)
            {
                fprintf(stderr, "%s is not a valid GUID \n", name);
                return;
            }
        }

        bmd_envelope->Destination = xmlStrdup(value);
        printf("Envelope Destination is valid %s \n", bmd_envelope->Destination);
    }

    if (xmlStrcmp(Signature, name) == 0)
    {
        ret = xmlTextReaderRead(reader);
        if (ret == 1)
            value = xmlTextReaderConstValue(reader);
        else
        {
            fprintf(stderr, "%s is not valid \n", name);
            return;
        }
        printf("Signature is %s \n", value);

        bmd_envelope->Signature = xmlStrdup(value);
    }

    if (xmlStrcmp(UserProperties, name) == 0)
    {
        //will implement
    }

    if (xmlStrcmp(ReferenceID, name) == 0)
    {
        ret = xmlTextReaderRead(reader);
        if (ret == 1)
            value = xmlTextReaderConstValue(reader);
        else
        {
            fprintf(stderr, "%s is not valid \n", name);
            return;
        }
        printf("ReferenceId %s \n", value);

        bmd_envelope->ReferenceID = xmlStrdup(value);
    }

    if (xmlStrcmp(CreationDateTime, name) == 0)
    {
        ret = xmlTextReaderRead(reader);
        if (ret == 1)
            value = xmlTextReaderConstValue(reader);
        else
        {
            fprintf(stderr, "%s is not valid \n", name);
            return;
        }
        printf("CreationDateTime %s \n", value);

        bmd_envelope->CreationDateTime = xmlStrdup(value);
    }

    if (xmlStrcmp(Payload, name) == 0)
    {
        ret = xmlTextReaderRead(reader);
        if (ret == 1)
            value = xmlTextReaderConstValue(reader);
        else
        {
            fprintf(stderr, "%s is not valid \n", name);
            return;
        }
        //printf("Payload %s \n", value);

        bmd_payload->data = xmlStrdup(value);
        int8_t Payload[100];
        strcpy(Payload,value);
        printf("Payload %s \n", Payload);
        
        xml2json(Payload);
    }
}

/**
 * streamFile:
 * @filename: the file name to parse
 *
 * Parse, validate and print information about an XML file.
 */
static void
streamFile(const char *bmd_file_path, envelope *bmd_envelope, payload *bmd_payload)
{
    xmlTextReaderPtr reader;
    int ret;

    /*
     * Pass some special parsing options to activate DTD attribute defaulting,
     * entities substitution and DTD validation
     */
    reader = xmlReaderForFile(bmd_file_path, NULL,
                              XML_PARSE_DTDATTR |      /* default DTD attributes */
                                  XML_PARSE_NOENT |    /* substitute entities */
                                  XML_PARSE_DTDVALID); /* validate with the DTD */
    if (reader != NULL)
    {

        ret = xmlTextReaderRead(reader);
        while (ret == 1)
        {
            process_nodes(reader, bmd_envelope, bmd_payload);
            ret = xmlTextReaderRead(reader);
        }
        /*
	 * Once the document has been fully parsed check the validation results
	 */

        // if (xmlTextReaderIsValid(reader) != 1)
        // {
        //     fprintf(stderr, "Document %s does not validate\n", bmd_file_path);
        // }
        xmlFreeTextReader(reader);
        if (ret != 0)
        {
            fprintf(stderr, "%s : failed to parse\n", bmd_file_path);
        }
    }
    else
    {
        fprintf(stderr, "Unable to open %s\n", bmd_file_path);
    }
}

static envelope *get_envelope_struct()
{
    envelope *bmd_envelope = (envelope *)malloc(sizeof(envelope));
    return bmd_envelope;
}

static payload *get_payload_struct()
{
    payload *bmd_payload = (payload *)malloc(sizeof(payload));
    return bmd_payload;
}

BMD *processXML(char *bmd_file_path)
{

    bmd_file_path = "/home/utkarsh/Documents/jhelum-master/esb_endpoint/src/bmd.xml";
    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    BMD *bmd = (BMD *)(malloc(sizeof(BMD *)));

    bmd->bmd_envelope = get_envelope_struct();
    bmd->bmd_payload = get_payload_struct();

    streamFile(bmd_file_path, bmd->bmd_envelope, bmd->bmd_payload);

    printf(" \n %s \n %s \n %s \n ", bmd->bmd_envelope->MessageID, bmd->bmd_envelope->MessageType, bmd->bmd_envelope->ReferenceID);
    printf("payload %s\n", bmd->bmd_payload->data);
    /*
     * Cleanup function for the XML library.
     */
    xmlCleanupParser();
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
    return (bmd);
}

#else
int processXML(void)
{
    fprintf(stderr, "XInclude support not compiled in\n");
    exit(1);
}
#endif

//WILL DO LATER --> IMPROVE CODE and PROCESS SIMILAR NODES in 1 FUNCTION , THIS CODE HAS TOO MANY REPEATED STATEMENTS
/*
get_node(xmlTextReaderPtr reader)
{
     ret = xmlTextReaderRead(reader);
        if (ret == 1)
            value = xmlTextReaderConstValue(reader);
        else
        {
            fprintf(stderr, "%s is not valid \n", name);
            return;
        }
        if (value != NULL)
        {
            int is_guid = check_if_string_is_guid(value);
            if (is_guid == 0)
            {
                fprintf(stderr, "%s is not a valid GUID \n", name);
                return;
            }
        }
}
*/
