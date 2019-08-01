#include<iostream>
#include<sys/socket.h>
#include<string>
#include<sys/types.h>
#include<cstring>
#include<netdb.h>
#include<errno.h>

using namespace std;
int main()
{
	string nick = "NICK Bot1999292\r\n";
        string user = "USER Bot Bot Bot :a bot\r\n";
	std::string channel = "JOIN #spe\r\n";
	std::string ping = "PONG :lindbohm.freenode.net\r\n";
	int connected = 0;
	
	struct sockaddr_in addr;
	struct hostent *host;
	int port = 6667;
	host = gethostbyname("irc.freenode.net");


	addr.sin_addr.s_addr = *(unsigned long*)host->h_addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons((unsigned short)port);

	int sockfd;
 	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("socket:");
	}

	int status;
	status = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if(status < 0)
	{
		perror("connect:");
	}

	cout << "Connecting to: irc.freenode.org" << endl;
        send(sockfd, nick.c_str(), nick.size(), 0);
        cout << "Sent: " << nick << " to server" << endl;
        send(sockfd, user.c_str(), user.size(), 0);
        cout << "sent: " << user << " to server" << endl;
	send(sockfd, channel.c_str(), channel.size(),0);
	std::cout << "Channel:" << channel << " to server" << std::endl; 
          char sockbuff[4096];
        while (connected < 1) {
		
		send(sockfd,ping.c_str(),ping.size(),0);
		memset(&sockbuff, '\0', sizeof(sockbuff));
                recv(sockfd, sockbuff, 4096, 0); 
                cout << sockbuff << endl;
        }
  return 0;
}
