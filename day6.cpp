#include <iostream>
using namespace std;


void avg_sum_max_min(int arr[],int size){
   int max=arr[0],min=arr[0];
   int sum=0;
   int maxP=0,minP=0,avg;
    for(int i=0;i<size;i++){
    
    sum=sum+arr[i];

    if(arr[i]>max){
        max=arr[i];
        maxP=i;
      }
    
    if(arr[i]<min){
    min=arr[i];
    minP=i;
    }

}

  avg=sum/size;
    cout<<"the minmum of integers is "<<min<<" at position"<<minP+1<<endl<<endl;
    cout<<"the maximum in array is "<<max<<" at position"<<maxP+1<<endl<<endl;
    cout<<"the sum in array is "<<sum<<endl<<endl;
    cout<<"the average of integers is "<<avg<<endl<<endl;

}

void reorder(int arr[],int size){
    int temp[5];
    int idx = 0;

       for (int i=0;i<size;i++){
        if (arr[i]%2==0){
            temp[idx++]=arr[i];
        }
    }

    
    for (int i=0;i<size;i++){
        if(arr[i] %2!=0) {
            temp[idx++]=arr[i];
        }
    }
    
    cout<<"the reorderd array is "<<endl;

    for (int i=0;i<size;i++){
        cout<<temp[i]<<"    ";
    }
}


int main(){
    int arr[5];
    cout<<"enter the five integers\n";
    for(int i=0;i<5;i++){
    cin>>arr[i];
    }
    avg_sum_max_min(arr,5);
    reorder(arr,5);
}