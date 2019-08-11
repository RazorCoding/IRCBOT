#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<regex>
#include<string>


int main()
{
    //IRC Arguments
 std::string nick = "NICK DS\r\n"; //NICK
 std::string user = "USER Bot Bot Bot :a bot\r\n"; // USer 
 std::string channel = "JOIN #test\r\n"; //Channel 
 std::string ping = "PONG :"; //PING
 std::string msg = "privmsg #default : PONG \r\n";//PING
 std::string ctcp = ""; //CTCP VERSION

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
 std::regex r ("PING\\s*:?(.*)"); // REGEX PING
 std::regex x ("[!]PING"); // REGEX PING FIND
 std::regex i (":[a-z]+!~[a-z]+@[a-z]+\.[a-z]+\s\w+\s\w+\s:\w+"); ?//CTCP VERSION
     
 //LOOP
 while (connected < 1) {
 memset(&sockbuff, '\0', sizeof(sockbuff));
    //PING SEND
    if (std::regex_search (buff, mt, r))
    {
            std::smatch::iterator it = mt.begin()+1;
            ping.append(*it);
            ping.append("\r\n");                         
            send(sockfd,ping.c_str(),ping.size(),0);
    }
     //!PING PONG
    if(std::regex_search(buff , mt,x))
    {
            send(sockfd,msg.c_str(),msg.size(),0);   
    }
     //CTCP VERSION SEND
    if(std::regex_search(buff, mt,i))
    {
            std::smatch::iterator yt = mt.begin()+1;
            ctcp.append(*yt);
            ctcp.append("\r\n");                    
            std::cout << ctcp << std::endl;
            send(sockfd,ctcp.c_str(),ctcp.size(),0);
   }
     //REACVING
    recv(sockfd,sockbuff,4096,0);
    buff = sockbuff;
    std::cout << buff << std::endl;
 }
  return 0; // RETURN 0;
}
