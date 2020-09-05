#include <stdio.h>
#include "email.h"
#include <bmd_parser.h>
#include <esb.h>
#include <stdlib.h>

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */

/** 
   *Parses the BMD to extract envelope and payload.
   *It returns a pointer to the struct BMD. 
*/
static BMD *parse_bmd_xml(char *bmd_file_path) 
{
    BMD *bmd; 
    bmd=process_xml(bmd_file_path);
    return bmd;
}
 /**
   *Checks whether the BMD is valid.
   *Return 1 if BMD is valid.
 */
static int is_bmd_valid(BMD *bmd)
{   int valid=1;   // valid =>1 , -ve for error.
     
      
      //If any of the envelope values are NULL the BMD is invalid.
      if(bmd->bmd_envelope->MessageID==NULL || 
         bmd->bmd_envelope->Sender==NULL ||
         bmd->bmd_envelope->Destination==NULL||
         bmd->bmd_envelope->MessageType==NULL ||
         bmd->bmd_envelope->Signature==NULL ||
         bmd->bmd_envelope->ReferenceID==NULL ||
         bmd->bmd_envelope->CreationDateTime==NULL ){
             
             valid=0;
             return valid;
         }

    //If MessageID is not a GUID BMD is invalid
          if(check_if_string_is_guid(bmd->bmd_envelope->MessageID)!=1)
            return 0;
    //If Sender is not a GUID BMD is invalid
          if(check_if_string_is_guid(bmd->bmd_envelope->Sender)!=1)
             return 0;    
     //If Destination is not a GUID BMD is invalid
          if(check_if_string_is_guid(bmd->bmd_envelope->Destination)!=1)
              return 0;

     /*If for given Sender , Destination and Message Type there is no
       Active route Present then the BMD is invalid.
       For a selected Route there must be records present in transport_config and transform_config tables
     */
           int route_id=select_active_route( bmd->bmd_envelope->Sender,
                                             bmd->bmd_envelope->Destination,
                                             bmd->bmd_envelope->MessageType);
           if( route_id>0)
           {
            if(select_transport_config(route_id) >0 && select_transform_config(route_id) >0)
             valid=1;
            else
             valid=0;
                      
                      
           }

         return valid;
}
/**
 * Takes a valid BMD as a parameter.
 * The contents of the envelope are written to esb_request table.
 * Returns 1 if successfully wriiten to a the table.
*/
int queue_the_request(BMD *bmd)
{
    int success=1; //success ==>1 , -ve for errors.
     sqlcon(bmd);   
     return success;
}


int process_esb_request(char* bmd_file_path) {
    int status = 0; // OK == 0
    printf("Handling the BMD %s\n", bmd_file_path);
    /** TODO: 
     * Perform the steps outlined in the Theory of Operation section of
     * the ESB specs document. Each major step should be implemented in
     * a separate module. Suitable unit tests should be created for all
     * the modules, including this one.
     */
     
     
    BMD *bmd; 
    bmd=parse_bmd_xml(bmd_file_path);      //To retrieve envelope bmd->bmd_envelope ,For payload use bmd->bmd_payload;
     
    if(is_bmd_valid(bmd))
     {
         queue_the_request(bmd);
     }
     else
     {
         status=-1;
     }
           
                                
     return status;
}

