#include<stdio.h>
#include "email.h"
#include <bmd_parser.h>
#include <esb.h>
#include <stdlib.h>
/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
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
    bmd=processXML(bmd_file_path);      //To retrieve envelope bmd->bmd_envelope ,For payload use bmd->bmd_payload;
     
     printf("BMD retrieved");        //Weird behaviour --> print statement gets executed only while printing some bmd elements 
                                      //Add printf("%s",bmd->bmd_envelope->MessageID);
     return status;
}
