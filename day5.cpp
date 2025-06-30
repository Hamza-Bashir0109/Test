#include <iostream>
using namespace std;
int factorialOf(int n) {
    if(n < 0){
        cout<<"invalid number\n";
        return 0;
    }

    int result=1;
    for(int i=2;i<=n;++i){
        result*=i;
    }

    return result;
}

int maxOfThree(int a,int b,int c){
    int max=a;

    if(b>max){
        max=b;
    }

    if (c>max){
        max=c;
    }

    return max;
}

int main(){
    int num;
    cout<<"Enter a postive number to calculate factorial of";
    cin>>num;

    int fact=factorialOf(num);
    if (num>=0){
        cout<<"Factorial of "<<num<<" is: " <<fact<<endl;
    }

    int x,y,z;
    cout<<"\nEnter three numbers:\n";
    cout<<"First: ";
    cin>>x;
    cout<<"Second: ";
    cin>>y;
    cout<<"Third: ";
    cin>>z;

    int max=maxOfThree(x,y,z);
    cout<< "Maximum is: "<< max<<endl;

    return 0;
}
