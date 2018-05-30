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
#include<fstream>

using namespace std;

      int client,server;
      int portNum = 3001;
      bool isExit = true;
      int bufSize = 256;
      char buffer[256];
      ifstream f1;
      ofstream f2;
      //ofstream f2;

void makeFile()
{
      int count =0,i;
      f1.open("firstFile.txt",ios::in);
      f2.open("secondFile.txt",ios_base::binary);

      char buffer;
      string str;

      while(f1 >> buffer)
      {
          f2 << buffer;
      }

      if(i=(count%64)) {
        while(i>0){
            f2 << '0';
        }
      };
      f1.close();
      f2.close();

      //f2.open("seconfFile.txt",ios::in);
      //f2.open("secondFile.txt",ios_base::binary)
}

int main()
{
      //char *ip = "10.100.109.85";

      client = socket(AF_INET,SOCK_STREAM,0);
      struct sockaddr_in server_addr;
      if(client<0)
      {
            cout << "Error creating socket...." << endl;
            //exit(1);
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
      recv(client,buffer,bufSize,0);
      //cout << buffer << endl;
      //cout << "conection confirmed" << endl;
      //cout << "you can connect server" << endl;
      /// << "send msg to server" << endl;

      makeFile();

      ifstream f3;
      f3.open("secondFile.txt",ios_base::binary);

      do{
            int i=0;
           // memset(buffer,'0',);
            while(i<64){
               f1 >> buffer[i];
               i++;
            }
               send(client,buffer,bufSize,0);
            break;
                 /*recv(client,buffer,bufSize,0);
                  cout<< buffer << endl;
                   if(*buffer=='B'){
                    isExit=false;*/
                   //}
      }while(!f1.eof());
      *buffer = 'B';
       send(client,buffer,bufSize,0);

      f3.close();
      //f2.close();
      // return 0;

      cout << "connection terminated" << endl;
      cout << "goodbye" << endl;
      close(client);

      return 0;
}
