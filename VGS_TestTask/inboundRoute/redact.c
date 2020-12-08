/*********Charley Chen********* 
Receiving from the page request to redact data:account_holder, account_number and account_CVV
request and save the redacted data on a file as a touch point in a designated web directory
result: redacted cardinfo : account_holder, account_number and account_CVV
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "request.h"
#include <json-c/json.h> 

int main(void) {

printf("Content-type:text/html\r\n\r\n");

FILE *file; 
char buffer[1024];
 
struct json_object  *creditCardInfo;  
struct json_object  *cardJson; 

char requestCardHolder[125] ;
char requestCardNumber[125];
char requestCardCVV[5];

request(requestCardHolder,"cardHolder");   
request(requestCardNumber,"cardNumber");   
request(requestCardCVV,"cardCVV");   

char requestRedact[355];  

// Make sure to add fields accordingly in the Json path when login VGS dashboard on route: inbound

strcpy(requestRedact,"curl https://<vault_id>.SANDBOX.verygoodproxy.com/post \\");  // need to update this <vault_id> to your environment before compile
strcat(requestRedact,"-H \"Content-type: application/json\" \\"); 

strcat(requestRedact,"-d '{\"account_holder\": \"");
strcat(requestRedact,requestCardHolder); 
 
strcat(requestRedact,"\",\"account_number\":\""); 
strcat(requestRedact,requestCardNumber); 
strcat(requestRedact,"\",\"account_CVV\":\""); 

strcat(requestRedact,requestCardCVV); 

strcat(requestRedact,"\"}' > /<directory>/json/VGS.json");  //need to update this <directory> to your environment before compile; touch point for the recieving the request and save it to a file on a permissible folder on the webserver directory    

//printf("Requesting through curl, sending for redaction: %s <br>",requestRedact); // Debug only, not to show on html for security  

system(requestRedact);    

file = fopen("/<directory>/json/VGS.json","r"); //need to update this <directory> to your environment before compile
fread(buffer, 1024, 1, file);
fclose(file);

creditCardInfo = json_tokener_parse(buffer);
 
json_object_object_get_ex(creditCardInfo,"json",&cardJson);    

printf("Card info redacted%s<br>",json_object_get_string(cardJson)); 

return 0; 

}


 


