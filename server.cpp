#include<iostream>
#include<string.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<fstream>
//#include<ofstream>

using namespace std;

int main()
{
      int client,server;

      int portNum = 3001;
      int bufSize = 256;
      char buffer[bufSize];

      struct sockaddr_in  server_addr;
      //int socketlen_t size;
     // int size;

      client = socket(AF_INET,SOCK_STREAM,0);

      if(client<0)
      {
            cout << "error establishing connection" << endl;
            exit(1);
      }

      cout << "server socket connection created " << endl;

      server_addr.sin_family =AF_INET;
      server_addr.sin_port =  htons(portNum);
      server_addr.sin_addr.s_addr = htons(INADDR_ANY);
      //server_addr.sin_zero;

      //BIND SOCKET
      if(bind(client,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
      {
           / cout << "error binding socket " << endl;
            exit(1);
      }

     // /cout << " loking for client " << endl;
      listen(client,1);

      socklen_t SockAddrSize = sizeof(server_addr);
      server = accept(client,(struct sockaddr*)&server_addr, &SockAddrSize);

      if(server<0){
       //cout << "error on accepting " << endl;
        exit(1);
      }

      if(server>0)
      {
            strcpy(buffer,"server connected ....../n");
            send(server,buffer,bufSize,0);
            //cout<< "connected with client" << endl;
            //cout<< "you can communicate now" << endl;
      }

     ofstream f1;
     f1.open("input.txt",ios_base::binary);

      do{
          recv(server,buffer,bufSize,0);
            cout<< buffer << endl;
             //while(f2 >> buffer)
            {
                 // f2 << buffer;
            }
             if(*buffer=='B')  break;

          send(server,buffer,bufSize,0); */
        }while(true);
        f2.close();
      close(client);
      return 0;
}
