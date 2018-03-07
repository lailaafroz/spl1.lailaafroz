#include<iostream>
#include<fstream>
#include<cstdio>

using namespace std;

int main()
{
      ifstream f1;
      ofstream f2;
      f1.open("flower.jpg",ios::in);
      f2.open("secondFile.txt",ios_base::binary);
      char buffer;
      //int count =0;
      
      while(f1 >> buffer)
      {   
          f2 << buffer;
      }
      f1.close(); 
      f2.close();
      return 0;
}
