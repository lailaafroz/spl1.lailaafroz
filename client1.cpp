#include<iostream>
#include<string.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include<netdb.h>

using namespace std;   

int main()
{   
      int client,server;
      int portNum = 3001;
      bool isExit = true;
      int bufSize = 100;
      char buffer[bufSize];
      //char *ip = "10.100.109.85";

      client = socket(AF_INET,SOCK_STREAM,0);
      struct sockaddr_in server_addr;
      if(client<0)
      {        
            cout << "Error creating socket...." << endl;
            exit(1);
      }

      cout << "client socket created...." << endl;
      
      server_addr.sin_family =AF_INET;
      server_addr.sin_port =  htons(portNum);
      //server_addr.in_addr.s_addr = htons(INADDR_ANY);

      //if(bind(client,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
      //{
       //     cout << "error binding socket " << endl;
       //     exit(1);
      //}
      
      socklen_t SockAddrSize = sizeof(server_addr);
      int status = connect(client, (struct sockaddr*) &server_addr, SockAddrSize);

      if(status==0)
      {
           // cout  <<  "connecting to server...." << endl;
      }
      //recv(client,buffer,bufSize,0);
      cout << buffer << endl;
      cout << "conection confirmed" << endl;
      cout << "you can connect server" << endl;
      cout << "send msg to server" << endl;
      do{  
             cin >> buffer ;
               send(client,buffer,bufSize,0);
            
                 recv(client,buffer,bufSize,0);
                  cout<< buffer << endl;
                   if(*buffer=='B'){
                    isExit=false;
                   }
      }while(isExit);

      cout << "connection terminated" << endl;
      cout << "goodbye" << endl;
      //close(client);

      return 0;
}
