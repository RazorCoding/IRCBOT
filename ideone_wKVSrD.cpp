#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<cstring>
#include<netdb.h>
#include<errno.h>
#include<chrono>


using namespace std;
int main(int argc, char *argv[])
{

	//IRC Arguments
	string nick = "NICK bot23224\r\n";
        string user = "USER Bot Bot Bot :a bot\r\n";
	std::string channel = "JOIN #bots\r\n";
	std::string ping = "PONG :\r\n";
        std::string msg = "privmsg #channel : Hi \r\n";	
	
	//Variables
	int connected = 0;
	struct sockaddr_in addr;
	struct hostent *host;
	int port = 6667;
	char Hostname = "irc.freenode.net";

	//gethostbyname
	
	host = gethostbyname(Hostname);
	
	//assigning IP Address
	addr.sin_addr.s_addr = *(unsigned long*)host->h_addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons((unsigned short)port);
	
	//Creating socket
	int sockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("socket:");
	}
	
	//Connecting socket
	int status =0;
	status = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if(status < 0)
	{
		perror("connect");
	}

	 // Send
	std::cout << "Connecting to: irc.freenode.org" << std::endl;
        send(sockfd, nick.c_str(), nick.size(), 0);
	std::cout << "Sent: " << nick << " to server" << std::endl;
        send(sockfd, user.c_str(), user.size(), 0);
	std::cout << "sent: " << user << " to server" << std::endl;
	send(sockfd, channel.c_str(), channel.size(),0);
	std::cout << "Channel:" << channel << " to server" << std::endl; 
	

	char str[] = "PINGr\r\n";
	 char str1[]= "!Hi\r\n";
	//Reacving
	char sockbuff[4096]; 
	while (connected < 1) {
                if(strcmp(str,sockbuff) != NULL )
		{
		   std::cout << "PONG:!" << std::endl;
		   send(sockfd, ping.c_str(), ping.size(),0); 
		}	
		if(strcmp(str1,sockbuff) != NULL)
		{
			send(sockfd, msg.c_str(), msg.size(),0);
		}
		memset(&sockbuff, '\0', sizeof(sockbuff)); 
		recv(sockfd,sockbuff,4096,0);
		std::cout << sockbuff << std::endl;	
 	}
  return 0;
}
