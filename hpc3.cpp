#include<iostream>
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void maxval(int arr[],int n){
    int maxval=arr[0];
    #pragma omp parallel for reduction(max:maxval)
    for(int i=0;i<n;i++){
        if(arr[i]>maxval){
            maxval=arr[i];
        }
    }
    cout<<"Maximum Value : "<<maxval<<endl;
}


void minval(int arr[],int n){
    int minval=arr[0];
    #pragma omp parallel for reduction(min:minval)
    for(int i=0;i<n;i++){
        if(arr[i]<minval){
            minval=arr[i];
        }
    }
    cout<<"Minimum Value : "<<minval<<endl;
}

void sum(int arr[],int n){
    int sum=0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
    cout<<"Summation : "<<sum<<endl;
}

void average(int arr[],int n){
    
}


