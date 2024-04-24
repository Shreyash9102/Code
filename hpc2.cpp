// #include<iostream>
// #include<bits/stdc++.h>
// #include<omp.h>
// using namespace std;

// void merge(int arr[],int l,int mid,int r){
//     int n1=mid-l+1;
//     int n2=r-mid;

//     int a[n1];
//     int b[n2];

//     for(int i=0;i<n1;i++){
//         a[i]=arr[l+i];
//     }
//     for(int j=0;j<n2;j++){
//         b[j]=arr[mid+1+j];
//     }

//     int i=0;
//     int j=0;
//     int k=l;

//     while(i<n1 && j<n2){
//         if(a[i]>b[j]){
//             arr[k]=b[j];
//             k++;
//             j++;
//         }
//         else{
//             arr[k]=a[i];
//             k++;
//             i++;
//         }
//     }
//     while(i<n1){
//         arr[k]=a[i];
//         k++;i++;
//     }
//     while(j<n2){
//         arr[k]=b[j];
//         k++;j++;
//     }
// }
// void mergesort(int a[],int l,int r){
//     if(l<r){
//         int mid=(l+r)/2;
//         #pragma omp parallel sections
//         {
//             #pragma omp section
//             {
//                 mergesort(a,l,mid);
//             }
//             #pragma omp section
//             {
//                 mergesort(a,mid+1,r);
//             }
//         }
//         merge(a,l,mid,r);
        
//     }
// }
// int main(){
//     int arry[10]={1,34,6,63,97,24,67,13,64,73};
//     // auto start_time=chrono::high_resolution_clock::now();
//     // mergesort(arry,0,9);
//     // auto end_time=chrono::high_resolution_clock::now();
//     // chrono::duration<double> parallel_duration=end_time-start_time;

//     auto starttime=omp_get_wtime();
//     mergesort(arry,0,9);
//     auto endtime=omp_get_wtime();


    
//     cout<<"SORTED ARRYA : ";
//     for(int i=0;i<10;i++){
//         cout<<arry[i]<<" ";
//     }
//     cout<<endl;
//     cout<<"TIME TAKEN BY PARALLEL PROGRAMING : "<<(endtime-starttime)<<endl;

//     // cout<<"TIME TAKEN BY PARALLEL PROGRAMING : "<<parallel_duration.count()<<endl;
//     cout<<endl;
// }


#include<iostream>
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;


void bubble(int a[],int n){
    int counter=1;
    while(counter<n){
        for(int i=0;i<n-counter;i++){
            if(a[i]>a[i+1]){
                swap(a[i],a[i+1]);  //creat a temp for swaping
            }
        }
        counter++;
    }
}
/*One common approach is the "odd-even" or "brick sort" variant of the Bubble Sort, which is more amenable to parallelization. 
In this approach, the array is divided into two phases:
Odd-even phase: Compare all odd indexed elements with their next even indexed elements.
Even-odd phase: Compare all even indexed elements with their next odd indexed elements.
These two phases ensure that every element in the array is compared and possibly swapped in each full pass (both phases), 
and they can be parallelized since each comparison within a phase is independent.*/

void pbubble(int arr[],int n){
    bool isSorted=false;
    while(!isSorted){
        isSorted=true;


        //Odd-even phase: Compare all odd indexed elements with their next even indexed elements.

        #pragma omp parallel for
        for(int i=1;i<n-1;i+=2){
            if(arr[i]>arr[i+1]){
                swap(arr[i],arr[i+1]);
                isSorted=false;
            }
        }


        //Even-odd phase: Compare all even indexed elements with their next odd indexed elements.

        #pragma omp parallel for
        for(int i=0;i<n-1;i+=2){
            if(arr[i]>arr[i+1]){
                swap(arr[i],arr[i+1]);
                isSorted=false;
            }
        }
    }
}

int main(){
    int n=10;
    int arry[10]={11,4,6,1,15,2,8,3,7,10};
    
    auto start=omp_get_wtime();
    pbubble(arry,n);
    auto end=omp_get_wtime();
    cout<<"sequential time "<<end-start<<endl;

    cout<<"SOARTED ARRYA : "<<endl;
    for(auto i:arry){
        cout<<i<<"  ";
    }
    cout<<endl;


    

}