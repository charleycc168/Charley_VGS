#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int main(void) {
printf("Content-type:text/html\r\n\r\n");

printf("<html> <head></head><body>");
 printf("<h5>Redact your credit card info</h5>");

printf("<form action=\"http://<directory>/cgi-bin/redact\" method=\"post\">"); // need to update this <directory> to your environment before compile
printf("<input type=text name=cardHolder placeholder=\"Card holder name \">");
printf("<br>");
printf("<input type=text name=cardNumber placeholder=\"16 digits credit card number \">");
printf("<br>");
printf("<input type=text name=cardCVV placeholder=\"CVV\">");
printf("<br>");
printf("<input type=submit name=submit value=submit>");
printf("</form></body>"); 



return 0; 

}




