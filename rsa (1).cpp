#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void encrypt_numeric()
{
    cout<<"Numeric Encryption Fucntion Called\n ";
   
    

}

void decrypt_numeric()
{
   cout<<"Numeric Decryption  Fucntion Called\n ";

 
    
}       
void encrypt_text()
{
    cout<<"Text Encryption Fucntion Called\n ";
   
    

}

void decrypt_text()
{
   cout<<"Text Decryption  Fucntion Called\n ";

 
    
}
int main()
{
    cout<<"________________________________________________________________________________\n";
    cout<<"Lets Explore the Cyber security  -- RSA  Algorithm  \n";
    menu:
    cout<<"\n________________________________________________________________________________\n";
    cout<<"\n1.Encrypt  Numeric Message \n2.Decrypt Numeric Message\n3.Encrypt Text Message\n4.Decrypt Text Message\n5.Exit Code\n";
    cout<<"________________________________________________________________________________\n";
    cout<<"Enter Choice Code :\t";

    int ch;
    cin>>ch;
    cout<<"\n";

    switch(ch)
    {
        case 1 :
            encrypt_numeric();
            goto menu;
        case 2:
            decrypt_numeric();
            goto menu;
         case 2:
            encrypt_text();
            goto menu;
         case 4:
            decrypt_text();
            goto menu;
        case 5: 
            exit(0);
        default: 
            cout<<"Invalid Input !";
            goto menu;
    }

    return 0;
}
