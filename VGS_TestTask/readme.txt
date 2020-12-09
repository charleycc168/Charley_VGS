***************************************************************************
How to integrate VGS (Very Good Security) System tutorial:
*************************************************************************** 

Integrating VGS Tokenization takes me some ramp up on concept below

Concept : 

The security is based on javascript and vault server in order to give alias(tokens) to mask the sensitive data.       

So that companies/users do not have to keep their own security to pass the PCI and other compliance in order to make the secure transactions. 

First log in to VGS sandbox: 

Notice that when you logged in the VGS, the sandbox vault automatically created your Access Credential (Settings: shown near the bottom navigation). 
You may need to create another one since you may not get the password upon the first creation.  

Link: https://dashboard.verygoodsecurity.com

Vault credential (need to be save upon creation): 
usr :<redacted username>
password: <redacted password>

Understand the route:

Inbound route is the route between your front html client page to your server, saving those redact alias data by VGS client javascript (Collect.js) or your own code.

Outbound route is the route between you and the third party which would involve revealing the redacted alias.

Creating route: Create route by the Routes tab on the left navigation check for the appropriate REVEAL (outbound) or REDACT(inbound).    

Once each route is created you can use the 'Code snippets' tab and create your favorite client side code (I use curl) for testing. 
Note that since the VGS kept cookie info, so when you logged in to VGS dashboard by selecting and using the vault, it will carry those vault info to the code snippet. 
However the username and password for 'Revealing snippet' would not:it would just have USERNAME:PASSWORD placeholder. 
At this point you need to substitute those username and password you kept on the vault credentials

Secure Payload on route:
You can use the VGS integration flow to secure traffic: go to VGS Collect navigation link on the left then go down to the 'secure traffic with our integration flow', click on the 'integration' link and click on Secure traffic. 
Next you would enter the upstream host for inbound route, if not just use the default and proceed to etablish the connection.
Then you can execute 'Code Snippets' or your execute your own inbound redact code to redact the data on the secured traffic connection you just established.
Go back to the 'Logs' on the dashboard and you will see a icon with 3 disks and a magnifying glass which means you can now secure the payload.
You can secure payload on the route by clicking on the route but 'Secure this payload button' will display and click to proceed.

You will get the option on the fields to be able to 'redact' or 'reveal' and press the button 'secure this payload' to proceed.

The following is a working example for the above transaction:   

On the inbound redaction snippet, run that in the unix command prompt, and you will get the redacted account number. 
    
curl https://<vault_id>.SANDBOX.verygoodproxy.com/post \
  -H "Content-type: application/json" \
  -d '{"account_number": "ACC00000000000000000"}'

Copy and paste the redacted account number on the outbound revealing snippet with the vault credential for username and password substituted 

curl https://echo.apps.verygood.systems/post -k \
  -x <username>:<password>@tntcjymabmt.SANDBOX.verygoodproxy.com:8080 \
  -H "Content-type: application/json" \
  -d '{"account_number": "<redacted account number>"}' 

Then your will notice it reveal back to the original account number: 

--------------------------------------------------------------------
{
  "args": {},
  "data": "{\"account_number\":\"ACC00000000000000000\"}",
  "files": {},
  "form": {},
  "headers": {
    "Accept": "*/*",
    "Connection": "close",
    "Content-Length": "41",
    "Content-Type": "application/json",
    "Host": "echo.apps.verygood.systems",
    "User-Agent": "curl/7.69.1",
    "Vgs-Request-Id": "2569......."
  },
  "json": {
    "account_number": "ACC00000000000000000"
  },
  "origin": ".........",
  "url": "https://echo.apps.verygood.systems/post"
}
-----------------------------------------------------------------------

Once I understand the tokenization principle, routes and how to use VGS dashboard, I am ready to make a simple integration by coding a couple web applications displaying both inbound redacting data and the outbound revealing data.


The code is written in C to use with CGI-BIN on your website:

It is tested and runs on the Unix (OpenBSD 6.7) system. However it still would work on other platforms as long as it compiles to the platform.  


Package dependencies to install to use with the standard C library:
 
http://ftp.openbsd.org/pub/OpenBSD/6.7/packages/i386/

json-c-0.13.1.tgz

First you need to set up your web environment to host them under your web directory. Also, under the root directory, create a directory for json data repository and name it 'json'. Giving the proper rights for the web access (need to be able to read and write). 

Next, put the .env (for the outbound data revealing: username, password and vault_id) file inside of the 'json' directory

On the .env file, please just substitute redacted credentials denoted with '<>' and make sure to leave everything else untouched.
  
Now we are ready to compile the CGI codes for both inbound and outbound separately on each respective folders

I use clang compiler,

make sure to compile with correct linker as the the generic syntax below, upon opening the folders

clang -lm -ljson-c -I/<include directory> -L/<lib directory> -o /<directory>/cgi-bin/<name of the C binary> C source <file.c>

Once you have compiled all the C source codes to each of the respective binary files in the CGI-BIN, you are ready to set your browser to the webpages which start the inbound redact and the outbound reveal data.    

Now, you need to log in to VGS dashboard and follow the instructions above to create both inbound and outbound routes with the field names same as you would define them on your Json file. 

Once you have created the proper routes, make sure to secure payload on the route as it appears on the log once you have requested the transaction on the following setup. 

On the inboundRoute and outboundRoute open all the C files (.c extension) and update all the denoted <directory> and <vault_id> in the source code for your environment before compiling. Then open the inboundRoute/requestCardInfo.c and outboundRoute/revealCardInfo.c look for the url under the html <form> tag to copy over to your browser's url for your web browser to start the front pages to enter your credit card data to be redact and reveal.

Once you have submitted for redact, it will send the request to VGS to redact and pass back the Json file through Curl on the backend to touch and save as VGS.json file for the redacted data. As a result, you will see those data being redacted upon returning the result from the webpage.  

And when submitted for reveal, it will get your username, password and vault_id credential from the .env file and send the request to VGS to reveal and pass back the Json file through Curl on the backend to touch and save as revealVGS.json file for the revealed data. As a result, you will see those data be revealed upon returning the result from the webpage.

Now you are able to redact and reveal the credit card data, you can log into the VGS dashboard and change the reveal and redact on each field on these routes and you will get those results updated based on your selections, toggle and have fun!

Pretty cool!, 
I enjoy it, learning, researching, coding, implementing and testing for the simple integration to really show the concept of data tokenization and how a company can bypass the liability of keeping the credit card info safe without the hassles.
