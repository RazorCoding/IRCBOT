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
//#include <openssl/applink.c>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <signal.h>


int main()
{
	int newsockfd;
	SSL_CTX *sslctx;
	SSL *cSSL;
	int ssl_err;
	        
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
	int port = 6697;
	char hostname[] = "irc.freenode.net";
	
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
		perror("connect:");
	}
	
	sslctx = SSL_CTX_new( SSLv23_server_method());
        SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);
        int use_cert = SSL_CTX_use_certificate_file(sslctx, "/serverCertificate.pem" , SSL_FILETYPE_PEM);
        int use_prv = SSL_CTX_use_PrivateKey_file(sslctx, "/serverCertificate.pem", SSL_FILETYPE_PEM);

        cSSL = SSL_new(sslctx);
        SSL_set_fd(cSSL, newsockfd );
        //Here is the SSL connect  
        ssl_err = SSL_connect(cSSL);
        
	//Error occurred,
	switch (SSL_get_error(cSSL, ssl_err))
	{
		case 1:
			std::cout << ssl_err;
		case 2:
			std::cout << ssl_err;
		case 3:
			std::cout << ssl_err;
	}
	
	// sending
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
	//std::regex x (!.*[A-Z]);

	while (connected < 1) {
	memset(&sockbuff, '\0', sizeof(sockbuff));
	
	   if (std::regex_search (buff, mt, r))
	   {
		   	std::smatch::iterator it = mt.begin()+1; // First match is entire s
			ping.append(*it);
			ping.append("\r\n");
			std::cout << ping;
			send(sockfd,ping.c_str(),ping.size(),0);
	   }
/*	   if(std::regex_search(buff , mt,x))
	   {
		std::cout << "!PONG" << std::endl;
	   }
	   recv(sockfd,sockbuff,4096,0);
	   buff = sockbuff;
	   std::cout << buff << std::endl;*/
	}
  return 0;
}
