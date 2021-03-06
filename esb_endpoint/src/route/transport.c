#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Apply transport service */
int Apply_transport_service(char URL[], char transport_service[], char SENDER[], char transform_key[]) {
    int status = 1;
    printf("entered into apply_transport_service");
    if (!strcmp(transport_service, "HTTP")) {
        printf("\nHTTP service applied\n");
        send_http_request(URL);
        return status;
    } else if (!strcmp(transport_service, "email")){ 
    	if(!strcmp(transform_key,"Json_transform")){
        char filename[100];
        strcpy(filename, SENDER);
    	strcat(filename, "Payload.json");
        printf("Enter file to read:\t");
        //scanf("%s", & filename);
        printf("\nemail service applied\n");
        int mail_status = send_mail(URL, filename);
        if (mail_status == 0) {
            printf("Mail sent\n");
            return status;
        } else {
            printf("Failed to send the Mail\n");
            status = 0;
        }
     }
     else if (! strcmp(transform_key,"Xml_transform")) {
        char filename[100];
        strcpy(filename, SENDER);
    	strcat(filename, "Payload.xml");
        printf("Enter file to read:\t");
        //scanf("%s", & filename);
        printf("\nemail service applied\n");
        int mail_status = send_mail(URL, filename);
        if (mail_status == 0) {
            printf("Mail sent\n");
            return status;
        } else {
            printf("Failed to send the Mail\n");
            status = 0;
        }
     }
    } 
     else if (!strcmp(transport_service, "SFTP")){ 
    	if(!strcmp(transform_key,"Xml_transform")){
        char filename[100];
        strcpy(filename, SENDER);
    	strcat(filename, "Payload.xml");
        printf("Enter file to read:\t");
        //scanf("%s", & filename);
        printf("\nSFTP service applied\n");
        int sftp_status = sftp_upload(filename,filename);
        if (sftp_status == 1) {
            printf("File sent to sftp\n");
            return status;
        } else {
            printf("Failed to send the file\n");
            status = 0;
        }
     } 
     else if(!strcmp(transform_key,"Json_transform")){
        char filename[100];
        strcpy(filename, SENDER);
    	strcat(filename, "Payload.json");
        printf("Enter file to read:\t");
        //scanf("%s", & filename);
        printf("\nSFTP service applied\n");
        int sftp_status = sftp_upload(filename,filename);
        if (sftp_status == 1) {
            printf("File sent to sftp\n");
            return status;
        } else {
            printf("Failed to send the file\n");
            status = 0;
        }
     } 
     	
    } else {
        status = 0;
        printf("\nNo service found\n");
    }
    return status;

}
