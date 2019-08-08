#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<cstring>
#include<netdb.h>
#include<errno.h>
#include<unistd.h>
#include<regex>
#include<string>

int main(int argc, char *argv[])
{

	//IRC Arguments
	std::string nick = "NICK bot23224\r\n";
	std::string user = "USER Bot Bot Bot :a bot\r\n";
	std::string channel = "JOIN #default\r\n";
	std::string ping = "PONG :";
        std::string msg = "privmsg #default : Pong \r\n";

	//Variables
	int connected = 0;
	struct sockaddr_in addr;
	struct hostent *host;
	int port = 6667;
	char hostname[] = "irc.freenode.net";
	SSL_CTX *sslctx;
	SSL *cSSL;
	//gethostbyname

	host = gethostbyname(hostname);

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
	std::cout << "Connecting to: "<< hostname << std::endl;
        send(sockfd, nick.c_str(), nick.size(), 0);
	std::cout << "Sent: " << nick << " to server" << std::endl;
        send(sockfd, user.c_str(), user.size(), 0);
	std::cout << "sent: " << user << " to server" << std::endl;
	send(sockfd, channel.c_str(), channel.size(),0);
	std::cout << "Channel:" << channel << " to server" << std::endl;

	//Reacving
	char sockbuff[4096];
	std::string buff = " ";
	std::smatch mt;
    	std::regex r ("PING\\s*:?(.*)");
	std::cout << buff << std::endl;

	while (connected < 1) {
	memset(&sockbuff, '\0', sizeof(sockbuff));
        recv(sockfd,sockbuff,4096,0);
	buff = sockbuff;

	std::cout << buff << std::endl;

	   if (std::regex_search (buff, mt, r))
	   {
		   	std::smatch::iterator it = mt.begin()+1; // First match is entire s
			ping.append(*it);
			ping.append("\r\n");
			std::cout << ping;
			send(sockfd,ping.c_str(),ping.size(),0);
	   }
	   if(buff.find("!PING") != std::string::npos);
	   {
		send(sockfd,msg.c_str(),msg.size(),0);

	   }
	}
  return 0;
}
