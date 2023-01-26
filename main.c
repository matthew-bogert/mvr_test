
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("\n");
    const char *runtype = argv[1];
    printf(" \n");
    printf("%s\n", runtype);
    printf("\n");
    const int result; 
    // Determine runtype (request or response)
    if (!strcmp(runtype, "Request")) {
        // run verifyRequest
        printf(" \n");
        sprintf(result, "%d", verifyRequest(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11]));
    } else if (!strcmp(runtype, "Record")) {
        // retrieve textblob from the given file, and run verifyRecord
        const char cleanRecord[5000] = {'\0'};
        sprintf(result, "%d", verifyRecord(cleanRecord));
    } else {
        // Shouldn't get to this block...
        sprintf(result, "%d", -1);
    }
    printf("%d\n", result);
    return result;
}

/** 
 * do whatever the state needs to verify the correct data exists
 * don't check for format for lic unless the state chokes on wrong data
 * we only check for Lic in WA
 */ 
int verifyRequest(char *reason, char *length, char *lic, char *lname, char *fname, char *dob, char *reference, char *subAccount, char *ssn, char *postbackURL){

  if ( lic == NULL || strlen(lic)< 12 ) {
    return -201;
  }
  return 0;
}

/**
 *  verifyRecord reads (clean) data from the state and determines what type of data it received
 * and if processing should continue. Very few states store data from this initial pass through
 * of data to store for later use if it helps.
 * to make life easier, we grab the status fields while checking data
 * then run through the record a second time to process
 * all the information, using the stored status fields
*/
int verifyRecord(char *cleanRecord)
{
//   ucase(cleanRecord);
//   ss("STATE", "WASHINGTON");

  if (strstr(cleanRecord, "<RESPONSEDESC>NORMAL</RESPONSEDESC>")) { 
    return 0;   // good search
  } 
  else if ( strstr(cleanRecord, "<RESPONSEDESC>DRIVER RECORD NOT FOUND</RESPONSEDESC>") 
    || strstr(cleanRecord, "<RESPONSEDESC>DECEASED</RESPONSEDESC>")) {            
    return 9999; //no hit
  } 
  else if (strstr(cleanRecord, "<RESPONSEDESC>ADR ACCESS DENIED</RESPONSEDESC>^")
    || strstr(cleanRecord, "THE SERVER WAS UNABLE TO PROCESS THE REQUEST DUE TO AN INTERNAL ERROR.")){
    return -301; //state unavailable, retry
  }
  else if ( strstr(cleanRecord, "<MESSAGE>THE MAXIMUM MESSAGE SIZE QUOTA FOR INCOMING MESSAGES")) {
    return 600; //record not available online
  }
  return -308; //further evaluation needed
}


