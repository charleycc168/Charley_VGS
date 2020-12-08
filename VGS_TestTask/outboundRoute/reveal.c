/*********Charley Chen********* 
Receiving from the page request to revealing redacted data:account_holder, account_number and account_CVV  
getting the redacted username and password along with the vault_id in the .env file on the designated web directory
request and save the revealed data on a file as a touch point in a designated web directory
result: revealed cardinfo : account_holder, account_number and account_CVV
*/
 
 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "request.h"
#include <json-c/json.h> 

int main(void) {

printf("Content-type:text/html\r\n\r\n");


char buffer[1024];
struct json_object  *creditCardInfo;
struct json_object  *cardJson;

char requestCardHolder[125] ;
char requestCardNumber[125];
char requestCardCVV[125];

request(requestCardHolder,"cardHolder"); 
request(requestCardNumber,"cardNumber"); 
request(requestCardCVV,"cardCVV"); 

FILE *filePointer = fopen("/<directory>/json/.env", "r"); // need to update this directory to your environment before compile

      if(filePointer == NULL) {
          perror("Unable to open file!");
          exit(1);
      }


	char entry[128];
	char entryValue[128];

	char requestReveal[355];  


	fgets(entry, sizeof(entry), filePointer) ;// get entry from .env file 
 
    	fclose(filePointer);

	// Make sure to add fields accordingly in the Json path when login VGS dashboard on route: outbound

		strcpy(requestReveal,"curl https://echo.apps.verygood.systems/post -k \\");
		strcat(requestReveal,"-x "); 
		strcat(requestReveal,entry) ;
		strcat(requestReveal,"-H \"Content-type: application/json\" \\") ;
		strcat(requestReveal,"-d '{\"account_holder\":\"");
		strcat(requestReveal,requestCardHolder);
		strcat(requestReveal,"\",\"account_number\":\"");
		strcat(requestReveal,requestCardNumber);
		strcat(requestReveal,"\",\"account_CVV\":\"");
		strcat(requestReveal,requestCardCVV);
		strcat(requestReveal,"\"}' > /<directory>/json/revealVGS.json");  //need to update this directory to your environment before compile; touch point for the recieving the request and save it to a file on a permissible folder on

		//printf("json query :%s\r\n", requestReveal); // Debug only, not to show on html for security 



	system(requestReveal);
 

filePointer = fopen("/<directory>/json/revealVGS.json","r"); // need to update this directory to your environment before compile
fread(buffer, 1024, 1, filePointer);
fclose(filePointer);

creditCardInfo = json_tokener_parse(buffer);

json_object_object_get_ex(creditCardInfo,"json",&cardJson);

printf("Card info revealed%s<br>",json_object_get_string(cardJson));

return 0;


}
