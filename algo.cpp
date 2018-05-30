#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ostream>

using namespace std;

ifstream iFile ;
ofstream oFile2;
oFile2.open("result.txt");
iFile.open("input.txt");
string message2,message1,rightTemporaryToHoldPreviousRightPart,encryptedOutput,message3,leftTemporaryToHoldPreviousRightPart,decryptedOutput,message4;
vector<string>key;
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


using namespace std;
int IP1_Table[64]={ 40,     8,   48,    16,    56,   24,    64,   32,
                     39,     7,   47,    15,    55,   23,    63,   31,
                     38,     6,   46,    14,    54,   22,    62,   30,
                     37,     5,   45,    13,    53,   21,    61,   29,
                     36,     4,   44,    12,    52,   20,    60,   28,
                     35,     3,   43,    11,    51,   19,    59,   27,
                     34,     2,   42,    10,    50,   18,    58,   26,
                     33,     1,   41,     9,    49,   17,    57,   25};

int IP_Table[64]= {58,    50,   42,    34,    26,   18,    10,    2,
           	 	   60,    52,   44,    36,    28,   20,    12,    4,
           		   62,    54,   46,    38,    30,   22,    14,    6,
           		   64,    56,   48,    40,    32,   24,    16,    8,
            	   57,    49,   41,    33,    25,   17,     9,    1,
                   59,    51,   43,    35,    27,   19,    11,    3,
                   61,    53,   45,    37,    29,   21,    13,    5,
                   63,    55,   47,    39,    31,   23,    15,    7};
int    E_BIT_SELECTION_TABLE[48]={  32,     1,    2,    3,     4,    5,
                                     4,     5,    6,     7,     8,    9,
                                     8,     9,   10,    11,    12,   13,
                                    12,    13,   14,    15,    16,  17,
                                    16,    17,   18,    19,    20,   21,
                                    20,    21,   22,    23,    24,   25,
                                    24,    25,   26,    27,   28,   29,
                                    28,    29,   30,    31,    32,    1};
int per[32]={16 ,  7 , 20  ,21,
                29 , 12 , 28 , 17,
                1 , 15,  23,  26,
                5 , 18 , 31  ,10,
                2  , 8 , 24 , 14,
                32  ,27,   3 ,  9,
                19  ,13,  30,   6,
                22 , 11  , 4 , 25};
 int s[8][4][16]=
    {{
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
    },
    {
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
    },


    {
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
    },
    {
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
    },
    {
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
    },
    {
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
    },
    {
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
    },
    {
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    }};


 void storingKeyFromFile()
{
	ifstream myfile;
	myfile.open("Key.txt");
	if(myfile.fail())
	{
		cout<<"could not open"<<endl;
	}
	else
	{
		string s;
		while(myfile>>s)
		{
			 key.push_back(s);
		}
	}
}


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
             char a,b;
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
      for(int k=0; k<48; k++)
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
          //cout << ffBit[i];
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

      for(int i=1; i<16; i++)
      {
           finalKey(i);
      }
}

string bit_conversion(string r)
{
    string s;
     for (int i=0;i<48;i++)
	{
    	s.push_back(r[E_BIT_SELECTION_TABLE[i]-1]);

	}
	//cout<<s<<endl;
	return s;
}

string XOR(string s, int i)
{
     string temp,key1;

        key1=key[i];
        //cout<<key1<<endl;
        for(int j=0;j<48;j++)
        {
             if(s[j]=='1'&&key1[j]=='1')
            {


                        char c='0';
                        temp=temp+c;

            }
                else if(s[j]=='0'&&key1[j]=='0')
                {


                        char c='0';
                         temp=temp+c;

                }
                else if(s[j]=='0'&&key1[j]=='1')
                {


                        char c='1';
                         temp=temp+c;

                }
                else if(s[j]=='1'&&key1[j]=='0')
                {

                        char c='1';
                         temp=temp+c;

                }

        }
        return temp;


}

void newMessage()
{
	for (int i=0;i<64;i++)
	{
    	message2.push_back(message1[IP_Table[i]-1]);
		//if(i % 2 == 1)
		  // key2.push_back(' ');
	}
	//cout<<message2<<endl;
}

string DES_Encryption(string l,string r)
{
    int round=0,i=0;
    string XOR_result,tempKey;
    while(round<16)
    {
    rightTemporaryToHoldPreviousRightPart=r;
        string expandedRightHalf= bit_conversion(rightTemporaryToHoldPreviousRightPart);
        //cout<<expandedRightHalf<<endl;
        //XOR_result=XOR(expandedRightHalf,0);

        //cout<<expandedRightHalf<<endl;


            XOR_result=XOR(expandedRightHalf,i);
          //s-box starts
          int row,col,temp;
          string sout="" , soutt="";
           for(int j=0;j<48;j+=6)

            {
                    row=(int(XOR_result[j+5])-48)+(int(XOR_result[j])-48)*2;
                    col= (int(XOR_result[j+1])-48)*8+(int(XOR_result[j+2])-48)*4+(int(XOR_result[j+3])-48)*2+(int(XOR_result[j+4])-48);
                    temp=s[j/6][row][col];
                    soutt="";
                    while(temp>0)
                    {
                        soutt+=char(temp%2+48);
                        temp/=2;
                    }
                    while(soutt.length()!=4)
                        soutt+='0';
                    for(int k=soutt.length()-1;k>=0;k--)
                        sout+=soutt[k];
            }
        //cout<<sout<<endl;
        //permutation
        char pc[32];
            for(int j=0;j<32;j++)
                pc[j]=sout[per[j]-1];
                r="";
                for(int k=0;k<32;k++)
                    r+=char(((int(pc[k])-48)^(int(l[k])-48))+48);
                    //cout<<r<<endl;
                    l=rightTemporaryToHoldPreviousRightPart;
                    //cout<<l<<endl;
                    encryptedOutput="";

     round++;
     i++;
    }
    encryptedOutput=r+l;
    for (int k=0;k<64;k++)++)
	{
    	message3.push_back(encryptedOutput[IP1_Table[k]-1]);
	}

    //cout<<message3<<endl;
    string output="";
     for(int j=0;j<64;j+=4)
            {
                int te;
                te=(int(message3[j])-48)*8+(int(message3[j+1])-48)*4+(int(message3[j+2])-48)*2+(int(message3[j+3])-48);
                if(te<10)
                    output+=char(te+48);
                else
                    output+=char(te+55);
            }
            //cout<<output<<endl;

return output;
}

void encryption(){

        while(true){
            for(int i=0; i<64; i++){
                iFile >> message1[i];
            }

        newMessage();
        leftPartOfMessage=message2.substr(0,32);
        //cout<<leftPartOfMessage<<endl;

        rightPartOfMessage=message2.substr(32,32);
        string k=DES_Encryption(leftPartOfMessage,rightPartOfMessage);
        oFile2 << k;

        if(!iFile.eof()) break;
        }
        oFile2.close();
}

string DES_decryption(string l,string r)
{
    int round=0,i=15;
    string XOR_result,tempKey;
    while(round<16)
    {
    rightTemporaryToHoldPreviousRightPart=r;
        string expandedRightHalf= bit_conversion(rightTemporaryToHoldPreviousRightPart);
        //cout<<expandedRightHalf<<endl;
        //XOR_result=XOR(expandedRightHalf,0);

        //cout<<expandedRightHalf<<endl;


            XOR_result=XOR(expandedRightHalf,i);
          //s-box starts
          int row,col,temp;
          string sout="" , soutt="";
           for(int j=0;j<48;j+=6)
            {
                    row=(int(XOR_result[j+5])-48)+(int(XOR_result[j])-48)*2;
                    col= (int(XOR_result[j+1])-48)*8+(int(XOR_result[j+2])-48)*4+(int(XOR_result[j+3])-48)*2+(int(XOR_result[j+4])-48);
                    temp=s[j/6][row][col];
                    soutt="";
                    while(temp>0)
                    {
                        soutt+=char(temp%2+48);
                        temp/=2;
                    }
                    while(soutt.length()!=4)
                        soutt+='0';
                    for(int k=soutt.length()-1;k>=0;k--)
                        sout+=soutt[k];
            }
        //cout<<sout<<endl;
        //permutation
        char pc[32];
            for(int j=0;j<32;j++)
                pc[j]=sout[per[j]-1];
                r="";
                for(int k=0;k<32;k++)
                    r+=char(((int(pc[k])-48)^(int(l[k])-48))+48);
                    //cout<<r<<endl;
                    l=rightTemporaryToHoldPreviousRightPart;
                    //cout<<l<<endl;
                    decryptedOutput="";

     round++;
     i--;
    }
    decryptedOutput=r+l;
    for (int k=0;k<64;k++)
	{
    	message4.push_back(decryptedOutput[IP1_Table[k]-1]);

	}

    //cout<<message3<<endl;
    string output="";
     for(int j=0;j<64;j+=4)
            {
                int te;
                te=(int(message4[j])-48)*8+(int(message4[j+1])-48)*4+(int(message4[j+2])-48)*2+(int(message4[j+3])-48);
                if(te<10)
                    output+=char(te+48);
                else
                    output+=char(te+55);
            }
            //cout<<output<<endl;

return output;
}

void decryption(){
     while(true){
            for(int i=0; i<64; i++){
                iFile >> message1[i];
            }

        newMessage();
        leftPartOfMessage=message2.substr(0,32);
        rightPartOfMessage=message2.substr(32,32);

        string k1=DES_decryption(leftPartOfMessage,rightPartOfMessage);
            oFile2 << k;
            if(!iFile.eof()) break;
        }
        oFile2.close();
}


int main()
{
      string enKey;
      //cout << "enter encryption key" << endl;
      //cin >> enKey;
      //cout << enKey;


      char command ;
      iFile >> command;

      for(int i=0; i<63; i++){
        iFile >> enKey[i];
      }

      makeKey(enKey);

      ofstream oFile;
      oFile.open("key.txt");

      for(int i=0; i<16; i++){
         for(int k=0; k<48; k++){
             oFile << arr[i][k];
         }
         oFile << endl;
      }

        storingKeyFromFile();

        if(command=='e') encryption();
        else decryption();

        iFile.close();
        return 0;
}
