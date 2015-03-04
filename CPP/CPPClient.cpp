#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
class Client
{
public:
	Client(char* serverIP);
    int Recv(char* filename);
private:

    int sockfd, n;
	char recvBuff[1024];
	struct sockaddr_in serv_addr; 
    int port;
    char* serverIP;

};

Client::Client(char* serverIP)	//constructor
{
    this->sockfd = 0;
    this->n = 0;
	this->port=27024;
	this->serverIP=serverIP;
    
}


int Client::Recv(char* filename)
{
	printf("Connecting to specified server\n");
	memset(this->recvBuff, '0',sizeof(this->recvBuff));
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Error: SOCKET ERROR\n");
		return 1;
	} 

	memset(&(this->serv_addr), '0', sizeof(this->serv_addr)); 

	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_port = htons(this->port); 

	if(inet_pton(AF_INET, this->serverIP, &(this->serv_addr.sin_addr))<=0)
	{
		printf("ERROR: inet_pton()\n");
		return 1;
	} 

	if( connect(this->sockfd, (struct sockaddr *)&(this->serv_addr), sizeof(this->serv_addr)) < 0)
	{
		printf("ERROR: Connect() \n");
		return 1;
	} 
	printf("Connected to Server\n");
    char ac[] = "C";
    write(this->sockfd, ac, sizeof(char)*2);

    unsigned int fileSize= -1;

	if( (n = read(this->sockfd, (char*)&fileSize, sizeof(unsigned int))) > 0)
	{
		printf("File Size for the request file is %d-%d\n",fileSize,n);
	}else{
		printf("\nClient Read error \n");
	} 
	char * fileArray_c = (char*)calloc(fileSize+10, sizeof(char));


	if( (n = read(this->sockfd, fileArray_c, fileSize+5 )) < 0)
	{
				printf("\nClient Read error \n");
	}
	

	FILE *fp = fopen(filename,"w");
        if(fp==NULL)
        {
            printf("FFOPEN ERROR");
            return -1;  
        }

            int nread = fwrite(fileArray_c,1,n,fp);
            printf("Bytes read %d \n", nread);        

            if (nread < fileSize)
            {
                if (feof(fp))
                    printf("ERROR: UNEXPECTED EOF\n");
                if (ferror(fp))
                    printf("ERROR: ERROR READING FILE\n");

            }

	fclose(fp);
	free(fileArray_c);
	return 0;

}

