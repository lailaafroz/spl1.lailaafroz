#include<iostream>
#include<fstream>

using namespace std;

int ip1 []={58 ,   50 , 42  , 34  ,  26  , 18  ,  10  ,  2,
            60  ,  52 , 44  , 36  ,  28  , 20  ,  12  ,  4,
            62  ,  54 , 46  , 38  ,  30  , 22  ,  14  ,  6,
            64  ,  56 , 48  , 40  ,  32  , 24  ,  16  ,  8,
            57  ,  49 , 41  , 33  ,  25  , 17  ,  9   ,  1,
            59  ,  51 , 43  , 35  ,  27  , 19  ,  11  ,  3,
            61  ,  53 , 45  , 37  ,  29  , 21  ,  13  ,  5,
            63  ,  55 , 47  , 39  ,  31  , 23  ,  15  ,  7
           };

int eSelectionBitTable[48] ={32 ,  1  ,  2   ,  3   ,   4  ,  5
                            4   ,  5  ,  6   ,  7   ,   8  ,  9
                            8   ,  9  ,  10  ,  11  ,  12  ,  13
                            12  , 13  ,  14  ,  15  ,  16  ,  17
                            16  , 17  ,  18  ,  19  ,  20  ,  21
                            20  , 21  ,  22  ,  23  ,  24  ,  25
                            24  , 25  ,  26  ,  27  ,  28  ,  29
                            28  , 29  ,  30  ,  31  ,  32  ,  1,
                            };

//char msg[][];
char msg1[64], msg2[64] , leftHalf[32], rightHalf[32] , left[16][48] , right[16][48] , key[16][48];

void expand(char *rh ,int xorCount){

    for(int i=0; i<48; i++){
    left[xorCount][i] =  rh[eSelectionBitTable[i]];
    }
}

string xor(char *str1, char *str2){
    string str3;

    for(int i=0; i< 48; i++){
        if(str1[i] == str2[i]) str3[i] =  "0";
        else str3[i] = "1";
    }
}

void encode(){
    //first parmutation to change 64 bit msg for the first time
    for(int i=0; i<64; i++){
        msg2[i] = msg1[ip1[i]-1];
    }

    for(int i=0; i<32; i++){
        leftHalf[i] = msg2[i];
        rightHalf[i] = msg2[i+32];
    }

    int xorCount = 1;
    expand(rightHalf ,xorCount);

    for(int i=1; i<=16; i++){
        string xorResult = xor(left[i],key[i]);
        right[i] = xor(xorResult,left[i-1]);
        if(i<16)  expand(right[i],i);
    }

}

void encrypt(){

    ifstream iFile1 , iFile2;
    iFile1.open("FirstFile.txt");
    iFile2.open("key.txt");

    for(int i=0; i<16; i++){
        for(int j=0; j<48; j++){
            iFile2 >> key[i][j];
        }
    }

    int count =0;

    while(!iFile1.eof()){

        iFile >>  msg1[count];
        count++;
        if(count==63){
            encode();
            count=0;
        }
    }
}

int main(){

    encrypt();
    return 0;
}
