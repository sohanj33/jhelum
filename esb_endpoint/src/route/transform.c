#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function to check and call the transformation required */
int check_transform(char type[], int route_id, char * transport_key, char * transport_value, char * SENDER) {
    if ((!strcmp(type, "Json_transform")) && (!strcmp(transport_value, "HTTP"))) {
        printf("\nApplying HTTP_Json transformation\n");
        HTTP_Json_transform(route_id, transport_key, SENDER);
        return 1;
    } else if ((!strcmp(type, "Json_transform")) && (!strcmp(transport_value, "email"))) {
        printf("\nApplying Email_Json transformation\n");
        get_emailID(route_id, transport_key);
        return 1;
    } else if ((!strcmp(type, "Xml_transform")) && (!strcmp(transport_value, "HTTP"))) {
        printf("\nApplying Email_Json transformation\n");
        HTTP_xml_transform(route_id, transport_key, SENDER);
        return 1;
    } else if ((!strcmp(type, "Xml_transform")) && (!strcmp(transport_value, "email"))) {
        printf("\nApplying Email_Json transformation\n");
        get_emailID(route_id, transport_key);
        return 1;
    }
    else if ((!strcmp(type, "Xml_transform")) && (!strcmp(transport_value, "SFTP"))) {
        printf("\nApplying SFTP_XML transformation\n");
        // Sftp_xml_transform(route_id, transport_key, SENDER);
         printf("Conversion done\n");
        return 1;
    } else if ((!strcmp(type, "Json_transform")) && (!strcmp(transport_value, "SFTP"))) {
        printf("\nApplying SFTP_Json transformation\n");
        // Sftp_json_transform(route_id, transport_key);
        printf("Conversion done\n");
        return 1;
    }
     else {
        printf("\nNo transformation needed\n");
        return 0;
    }

}

/* Transformation for having transport request as HTTP
 * And File format to be json
  */
// void Sftp_json_transform(route_id, transport_key, SENDER)
// {
//     char temp[100];
//     char * filename;
//     strcpy(filename, SENDER);
//     strcat(filename, "Payload.json");
//     FILE * fp = fopen(filename, "r");
//     fp = fopen(filename, "r");

//     if (fp == NULL)
//         return;

//     int i = 0;
//     char c = fgetc(fp);
//     while (c != EOF) {
//         temp[i++] = c;
//         c = fgetc(fp);
//     }
//     temp[i] = '\0';

//     char payload[strlen(temp)];
//     int k = 0;
//     for (int i = 0; i < strlen(temp); i++) {
//         if (temp[i] == ':') {
//             for (int j = i + 2; j < strlen(temp); j++) {
//                 if (temp[j] == '"')
//                     break;
//                 payload[k++] = temp[j];
//             }
//             break;
//         }
//     }

//     printf("\nPayload:\t%s\n", payload);

//     add_payload(payload, route_id, transport_key);
//     // printf("Conversion started\n");
//     // char temp[100];
//     // char * filename;
//     // strcpy(filename, SENDER);
//     // strcat(filename, "Payload.json");
//     // //create jsonStore folder to save files
//     // //to make unique json file,add messageID
//     // //sprintf(filename, "../jsonStore/payload%s.json", bmd->bmd_envelope->MessageID);
//     // //Create file and format payload as JSON
//     // FILE * fp = fopen(filename, "r");
//     // fp = fopen(filename, "r");

//     // if (fp == NULL)
//     //     return;

//     // int i = 0;
//     // char c = fgetc(fp);
//     // while (c != EOF) {
//     //     temp[i++] = c;
//     //     c = fgetc(fp);
//     // }
//     // temp[i] = '\0';

//     // char payload[strlen(temp)];
//     // int k = 0;
//     // for (int i = 0; i < strlen(temp); i++) {
//     //     if (temp[i] == ':') {
//     //         for (int j = i + 2; j < strlen(temp); j++) {
//     //             if (temp[j] == '"')
//     //                 break;
//     //             payload[k++] = temp[j];
//     //         }
//     //         break;
//     //     }
//     // }

//     // //fprintf(fp,"{\n \"Payload\":\"%s\"\n}",payload);
// 	// //confirmation message
//     // printf("\nPayload json File created\n");
//     // add_payload(payload, route_id, transport_key);
// }
// void Sftp_xml_transform(route_id, transport_key, SENDER)
// {
//     char temp[100];
//     char * filename;
//     strcpy(filename, SENDER);
//     strcat(filename, "Payload.json");
//     FILE * fp = fopen(filename, "r");
//     fp = fopen(filename, "r");

//     if (fp == NULL)
//         return;

//     int i = 0;
//     char c = fgetc(fp);
//     while (c != EOF) {
//         temp[i++] = c;
//         c = fgetc(fp);
//     }
//     temp[i] = '\0';

//     char payload[strlen(temp)];
//     int k = 0;
//     for (int i = 0; i < strlen(temp); i++) {
//         if (temp[i] == ':') {
//             for (int j = i + 2; j < strlen(temp); j++) {
//                 if (temp[j] == '"')
//                     break;
//                 payload[k++] = temp[j];
//             }
//             break;
//         }
//     }

//     printf("\nPayload:\t%s\n", payload);

//     add_payload(payload, route_id, transport_key);
//     // char temp[100];
//     // char * filename;
//     // strcpy(filename, SENDER);
//     // strcat(filename, "Payload.xml");
//     // //create jsonStore folder to save files
//     // //to make unique json file,add messageID
//     // //sprintf(filename, "../jsonStore/payload%s.json", bmd->bmd_envelope->MessageID);
//     // //Create file and format payload as JSON
//     // FILE * fp = fopen(filename, "r");
//     // fp = fopen(filename, "r");

//     // if (fp == NULL)
//     //     return;

//     // int i = 0;
//     // char c = fgetc(fp);
//     // while (c != EOF) {
//     //     temp[i++] = c;
//     //     c = fgetc(fp);
//     // }
//     // temp[i] = '\0';

//     // char payload[strlen(temp)];
//     // int k = 0;
//     // for (int i = 0; i < strlen(temp); i++) {
//     //     if (temp[i] == ':') {
//     //         for (int j = i + 2; j < strlen(temp); j++) {
//     //             if (temp[j] == '"')
//     //                 break;
//     //             payload[k++] = temp[j];
//     //         }
//     //         break;
//     //     }
//     // }

//     // //fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<?xml-stylesheet type='text/xsl'?>\n<payload>%s</payload>", payload);
// 	// //confirmation message
//     // printf("\nPayload json File created\n");
//     // add_payload(payload, route_id, transport_key);

// }



void HTTP_Json_transform(int route_id, char * transport_key, char * SENDER) {
    char temp[100];
    char * filename;
    strcpy(filename, SENDER);
    strcat(filename, "Payload.xml");
    FILE * fp = fopen(filename, "r");
    fp = fopen(filename, "r");

    if (fp == NULL)
        return;

    int i = 0;
    char c = fgetc(fp);
    while (c != EOF) {
        temp[i++] = c;
        c = fgetc(fp);
    }
    temp[i] = '\0';

    char payload[strlen(temp)];
    int k = 0;
    for (int i = 0; i < strlen(temp); i++) {
        if (temp[i] == ':') {
            for (int j = i + 2; j < strlen(temp); j++) {
                if (temp[j] == '"')
                    break;
                payload[k++] = temp[j];
            }
            break;
        }
    }

    printf("\nPayload:\t%s\n", payload);

    add_payload(payload, route_id, transport_key);

}
void HTTP_xml_transform(int route_id, char * transport_key, char * SENDER) {
    char temp[100];
    char * filename;
    strcpy(filename, SENDER);
    strcat(filename, "Payload.xml");
    FILE * fp = fopen(filename, "r");
    fp = fopen(filename, "r");

    if (fp == NULL)
        return;

    int i = 0;
    char c = fgetc(fp);
    while (c != EOF) {
        temp[i++] = c;
        c = fgetc(fp);
    }
    temp[i] = '\0';

    char payload[strlen(temp)];
    int k = 0;
    for (int i = 0; i < strlen(temp); i++) {
        if (temp[i] == ':') {
            for (int j = i + 2; j < strlen(temp); j++) {
                if (temp[j] == '"')
                    break;
                payload[k++] = temp[j];
            }
            break;
        }
    }

    printf("\nPayload:\t%s\n", payload);

    add_payload(payload, route_id, transport_key);

}
