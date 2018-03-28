#include<iostream>
#include<string>
#include<vector>

using namespace std;

char intKey[64];
int index=0;
char ffBit[56], c[17][28], d[17][28];
int enpc1[]=  {57 ,  49  ,  41  , 33 ,   25 ,   17  , 9,
               1 ,  58  ,  50  , 42  ,  34  ,  26  , 18,
              10  ,  2  , 59   ,51  ,  43  ,  35 ,  27,
              19  , 11   ,  3  , 60  ,  52  ,  44  , 36,
              63  ,55,47 ,39  ,31 ,23 ,15,
                 7, 62,  54  ,46 , 38, 30 , 22,
                14  ,  6  ,  61  , 53 ,   45   , 37,  29,
                21  , 13  ,   5   ,28  ,  20   , 12  ,  4};              
int enpc2[] =  {14,    17,   11,    24,     1,    5,
                3,     28,   15,     6,    21,   10,
                23,    19,   12,     4,    26,    8,
                16,     7,   27,    20,    13,    2,
                41,    52,   31,    37,    47,   55,
                30,    40,   51,    45,    33,   48,
                44,    49,   39,    56,    34,   53,
                46,    42,   50,    36,    29,   32
                };          
              
char arr[16][48];
void binary(char ch)
{
      int n,j=0,temp[4];
      for(int i=0; i<4; i++)
      {
           temp[i]=0;
           //cout << temp[i];
      }
      
      if(ch>='0' && ch<='9')  n= ch-48;
      else if(ch>='A' && ch<='F') n= ch-55;
      //cout << n ;
      
      while(n!=0 && j<4)
      {
           temp[j]= n%2;
           n=n/2;
           //cout << temp[j];
           j++; 
      }
      
      for(int k=3; k>=0; k--)
      {
            //if(index >55) break;
            intKey[index] = (char)(temp[k]+48);
            index++; 
            //cout << (char)(temp[k]+48); 
            //cout << (char)(temp[k]+48);
      }
}

void shift(int i, int p)
{
      for(int j=0; j<28; j++)
      {
          c[i][j]=c[i-1][j];
            d[i][j]=d[i-1][j];
      }

      while(p){
          for(int k=0; k<p; k++)
          {
             int a,b;
              a= c[i][27];
               b= d[i][27];
               
             for(int m=0; m<27; m++)
             {
                  c[i][m]=c[i][m+1];
                   d[i][m]=d[i][m+1];
             }
             c[i][27] = a;
             d[i][27] = b;
          }
          p--;  
      }
}

void finalKey(int i)
{          
      for(int k=0; k<48; i++)
      {
         int n= enpc2[k];
         if(n>27){
            arr[i-1][k] = d[i-1][n-29];
         }
         else
         arr[i-1][k] = c[i-1][n-1];
      }
}

void makeKey(string enKey)
{
      for(int i=0; i<16; i++)
      {     
            //cout << enKey[i];
            binary(enKey[i]);
      }
      
      index =0;
      for(int i=0; i<56; i++)
      {
          ffBit[i]= intKey[enpc1[i]];
      }
      
      
      for(int i=0; i<28; i++)
      {
          c[0][i]=ffBit[i];
          d[0][i]=ffBit[i+28];
      }
      
      for(int i=1; i<17; i++)
      {
          int p=2;
          if(i==1 || i==0 || i==8 || i==15) p=1;
          shift(i,p);
      }
      
      //delete [] ffBit;
      //delete [] enpc1;  
      
      for(int i=0; i<16; i++)
      {
           finalKey(i);  
      }
}

int main()
{ 
      string enKey;
      cout << "enter encryption key" << endl;
      cin >> enKey;
      //cout << enKey;
      makeKey(enKey);
      /*
      for(int i=0; i<16; i++){
         for(int k=0; k<48; k++){
             cout << arr[i][k];
         }
         cout << endl;
      }*/  
      return 0;
}
