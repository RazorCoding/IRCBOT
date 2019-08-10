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
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <signal.h>
#include<unistd.h>


int main()
{
	//SSL_CTX *sslctx;
	//SSL *cSSL;
	//int ssl_err;
	        
	//IRC Arguments
	std::string nick = "NICK DS\r\n";
	std::string user = "USER Bot Bot Bot :a bot\r\n";
	std::string channel = "JOIN #test\r\n";
	std::string ping = "PONG :";
        std::string msg = "privmsg #default : PONG \r\n";
	std::string ctcp = "";
	//Variables
	int connected = 0;
	struct sockaddr_in addr;
	struct hostent *host;
	int port = 6667;
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
	

	// SSL--SOCKET
	
	/*sslctx = SSL_CTX_new( SSLv23_server_method());
        if(!sslctx)
	{
		perror("Unable to create SSL context:");
		ERR_print_errors_fp(stderr);
		 exit(EXIT_FAILURE);
	}
	SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);
        int use_cert = SSL_CTX_use_certificate_file(sslctx, "/etc/ssl/certs/GTS_Root_R4.pem" , SSL_FILETYPE_PEM);
	if(use_cert <= 0)
	{
		perror("Cert:");
		ERR_print_errors_fp(stderr);
 		exit(EXIT_FAILURE);
	}
	int use_prv = SSL_CTX_use_PrivateKey_file(sslctx, "/etc/ssl/certs/GTS_Root_R4.pem", SSL_FILETYPE_PEM);
	if(use_prv <= 0)
	{
		perror("PRIVATE KEY:");
		ERR_print_errors_fp(stderr);
 		exit(EXIT_FAILURE);
	}

        cSSL = SSL_new(sslctx);
        SSL_set_fd(cSSL, sockfd );
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
	*/	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror( "SOCKET: ");
	}

	int status = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if(status < 0)
	{
		perror("connect:");
	}
	// sending
	std::cout << "Connecting to: "<< hostname << std::endl;
        send(sockfd, nick.c_str(), nick.size(), 0);
	std::cout << "Sent: " << nick << " to serveir" << std::endl;
        send(sockfd, user.c_str(), user.size(), 0);
	std::cout << "sent: " << user << " to server" << std::endl;
	send(sockfd, channel.c_str(), channel.size(),0);
	std::cout << "Channel:" << channel << " to server" << std::endl;

	//Reacving
	char sockbuff[4096];
	std::string buff = " ";
	std::smatch mt;
    	std::regex r ("PING\\s*:?(.*)");
	std::regex x ("[!]PING");
	std::regex i (":[a-z]+!~[a-z]+@[a-z]+\.[a-z]+\s\w+\s\w+\s:\w+");
	while (connected < 1) {
	memset(&sockbuff, '\0', sizeof(sockbuff));
	
	   if (std::regex_search (buff, mt, r))
	   {
		   	std::smatch::iterator it = mt.begin()+1; // First match is entire s
			ping.append(*it);
			ping.append("\r\n");
			send(sockfd,ping.c_str(),ping.size(),0);
	   }
	  if(std::regex_search(buff , mt,x))
	   {	
		send(sockfd,msg.c_str(),msg.size(),0);
	   }
	  if(std::regex_search(buff, mt,i))
	  {
	   std::smatch::iterator yt = mt.begin()+1;
	   ctcp.append(*yt);
	   ctcp.append("\r\n");
	   std::cout << ctcp << std::endl;
	   send(sockfd,ctcp.c_str(),ctcp.size(),0);
	  }
	   recv(sockfd,sockbuff,4096,0);
	   buff = sockbuff;
	   std::cout << buff << std::endl;
	}
  return 0;
}
