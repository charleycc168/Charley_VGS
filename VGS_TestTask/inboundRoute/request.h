#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define unHex(Y) (Y>='0' && Y<='9'?Y-'0':Y-'A'+10)

static char script[99999];

static void request(char *value, const char *param) {

script[sizeof(script)-1] = '\0'; 

if( getenv("REQUEST_METHOD")  ==  0 ) {  

		printf("No REQUEST_METHOD, must be running in DOS mode");
} else if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0 ) {

		char *pointTrailer ; // neccessary and required
		char *length = getenv("CONTENT_LENGTH");
		int Length = strtol(length, &pointTrailer, 10);
		fread(script, Length, 1, stdin);
} else {

		strcpy(script,getenv("QUERY_STRING")); 
		strcat(script,"\0"); 
}

char *scribe = strstr(script,param);

	if(scribe) {
	scribe += strlen(param);

		if(*scribe == '=') {
		scribe++;  //incrementing pointer 

		 while (*scribe && *scribe != '&') { 
			if (*scribe== '%') { // Convert it to a single ASCII character and store at our Valueination
			*value++ = (char)unHex(scribe[1]) * 16 + unHex(scribe[2]);
			scribe += 3;
			} else if( *scribe=='+' ) { // If it's a '+', store a space at our valueination
			*value++ = ' ';
			scribe++;
			} else {
			*value++ = *scribe++; // Otherwise, just store the character at our valueination
			}
		}

		*value ='\0'; 
		return; 

		}
	}

	strcpy(value,"value is undefine"); 
	return;
}
