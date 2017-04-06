#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>  //necessary header files for sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <string.h>
#include <unistd.h>

#define portnum 80

/* TCP Client Program */

int main(int argc, char *argv[]) //considering the command line arguments
{
	struct sockaddr_in server;  
	struct hostent *host;   
    	char buffer[5000];  
    	int socky,n;
	if((socky = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
        	perror("\n Error in socket creation");       //socket creation
        	exit(-1);
    	}
	printf("\n Socket successfully created"); 
	server.sin_family = AF_INET;
	server.sin_port = htons(portnum); //convert from host to network byte order format for portability
	host = gethostbyname(argv[1]);  //resolving host to IP
 	if(host == NULL)
	{
	        perror("\nError in getting host address");
	        exit(-1);
   	}

	memcpy (&server.sin_addr.s_addr, host->h_addr,host->h_length);
	if((connect(socky,(struct sockaddr*)&server,sizeof(server)))<0) //connecting to the server
	{
		perror("\n Error in connection");
		exit(1);
	}
	//while(1)
	//{
		char concat[2000];
		strcpy(concat,"GET "); 
		strcat(concat,argv[1]);
		strcat(concat," HTTP/1.1");
		strcat(concat,"\n\n");
		printf("\n %s",concat);
    		if((n = write(socky,concat,strlen(concat))) < 0)
    		{
        		perror("\nerror in writing the message");
        		exit(1);
    		}
		bzero(buffer,5000);
		if (n = (read(socky,buffer,1000)) < 0)
    		{
    			perror("\nerror in reading from socket");
    			exit(1);
    		}
    		printf("\nmessage recieved:%s",buffer);
	//}
	
	return 0;
}

























