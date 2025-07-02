#include <iostream>
#include <string>
using namespace std;

bool validate(const string& a){
    int i;
    
   for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == ' ') {
            return false;
        }
    }
    return true;
}

int validate_length(const string& a){
    int i=0;
    int vowel=0;
    
    while (a[i] != '\0') 
    {
        
         if(a[i]=='a'|| a[i]=='e'|| a[i]=='i' ||a[i]=='o' || a[i]=='u'){
            vowel++;
         }
         i++;
    }
    cout<<"The length of string is "<<i<<endl;
    cout<<"The number of vowel appear are "<<vowel<<endl;
    return i;
}
void reverse_string(string& input,int len){

     cout<<"Printing original string \n"<<input<<endl;
     cout<<"Printing reverse string \n";

     for(int i=len-1;i>=0;i--){
        cout<<input[i];
     }
}
void Palindrome(const string& a,int len){
    
    for (int i=0;i< len/2;i++){
        if (a[i]!=a[len-i-1]){
            cout<<"Not a palindrome\n";
        }
    }
    cout<<"Is a palindrome\n";
}
bool Uppercase(char ch){
    return (ch>='A' && ch<='Z');
}

void Lowercase(string& a){
    for(int i = 0; a[i]!='\0';i++){
        if (Uppercase(a[i])) {
            a[i]=a[i]+32; 
        }
    }
    cout<<a;
}
int main(){
    string input;
    cout<<"enter a string with no spaces\n";
    getline(cin,input);
    if (!validate(input)) {
        cout<<"Invalid Input no spaces or symbols allowed"<<endl;
        return 0;
    }
    int length=validate_length(input);
    reverse_string(input,length);
    Palindrome(input,length);
    Lowercase(input);

}