#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int main(void) {

printf("Content-type:text/html\r\n\r\n");

printf("<html> <head></head><body>");
printf("<h5>Reveal your redacted card info</h5>");

printf("<form action=\"http://192.168.200.107/cgi-bin/reveal\" method=\"post\">");

printf("<input type=text name=cardHolder placeholder=\"Redacted card holder name \">");
printf("<br>");
printf("<input type=text name=cardNumber placeholder=\"Redacted card number \">");
printf("<br>");
printf("<input type=text name=cardCVV placeholder=\"Redacted CVV\">");
printf("<br>");
printf("<input type=submit name=submit value=submit>");

printf("</form></body>"); 

return 0; 

}




