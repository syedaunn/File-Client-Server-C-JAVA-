#include <sys/socket.h>
#include<sys/ioctl.h>
#include<sys/stat.h>
#include<net/if.h>
#include<netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <dirent.h>
#include <limits.h>

char* fileArray =NULL;

class Server
{
public:
	Server();
	void Setup();
	void ServeClient(int connfd);

private:
	int port;
	int listenfd, connfd;
	struct sockaddr_in serv_addr; 

};

Server::Server()	//constructor
{
	this->listenfd = 0;
	this->connfd = 0;
	this->port = 33339;
	
}

void Server::Setup()	//Setup
{
	char sendBuff[1025];
	memset(sendBuff, '0', sizeof(sendBuff)); 
	memset(&(this->serv_addr), '0', sizeof(this->serv_addr));
	this->listenfd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(this->port); 

	bind(this->listenfd, (struct sockaddr*)&(this->serv_addr), sizeof(this->serv_addr)); 

	listen(listenfd, 5); 

	while(1)
	{
		printf("Waiting for Incoming Connection\n");
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
		printf("Connected\n");
		this->ServeClient(connfd);
		close(connfd);
		sleep(1);
	}
}

void Server::ServeClient(int connfd)	//Run
{
	
	char* fileToSend = "/home/aunn/testSend";
	struct stat fileStats;
	stat(fileToSend, &fileStats);
    int fileSize =  fileStats.st_size;
    printf("Size of %s is %ld bytes\n", fileToSend, fileStats.st_size);

	char ac[5] = "XXXX";
	int n=0;
	if( (n = read(connfd, ac, 5)) > 0)
	{
		printf("Client -> %s\n",ac);
	}else{
		printf("\nSOCKET READ ERROR\n");
	} 
	
	if(ac[0]== 'C'){
		printf("Client from Clang connected\n");
		write(connfd, (char*)&fileSize, sizeof(int));
	}
	fileArray =(char*) calloc(fileSize+10,sizeof(char));
	FILE *fp = fopen(fileToSend,"r");
	if(fp==NULL)
    {
        printf("FOPEN ERROR");
		return;
	}
   		

	int nread = fread(fileArray,1,fileSize,fp);
	printf("N read %d \n", nread);
    if(nread > 0)
    {
       write( connfd,(char*)fileArray, nread+1);
    }


    if (nread < fileSize)
        if (ferror(fp) || feof(fp))
            printf("ERROR: UNABLE TO READ FILE\n");

fclose(fp);
free(fileArray);

}

