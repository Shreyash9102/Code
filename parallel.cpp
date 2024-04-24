#include<iostream>
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int sum_serial(int n){
    int sum=0;
    for(int i=0;i<=n;i++){
        sum+=i;
    }
    return sum;
}

int sum_parallel(int n){
    int sum=0;
    #pragma omp parallel for reduction(+:sum)
       for(int i=0;i<=n;i++){
        sum+=i;
       }
    return sum;
}

int main(){
    const int n=100000000;
    auto start_time=chrono::high_resolution_clock::now();
    int result_serial=sum_serial(n);
    auto end_time=chrono::high_resolution_clock::now();
    chrono::duration<double> serial_duration=end_time-start_time;

    
    start_time=chrono::high_resolution_clock::now();
    int result_parallel=sum_parallel(n);
    end_time=chrono::high_resolution_clock::now();
    chrono::duration<double> parallel_duration=end_time-start_time;

    cout<<"Serial result "<<result_serial<<endl;
    cout<<"serial Duration "<<serial_duration.count()<<endl;
    cout<<"Parallel Result "<<result_parallel<<endl;
    cout<<"Parallel Duration "<<parallel_duration.count()<<endl;


    cout<<"SPEED UP "<<serial_duration.count()/parallel_duration.count()<<endl;


}