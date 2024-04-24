#include<iostream>
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

// void parallelDFS(vector<vector<int>>& graph,int startnode){
//     int numNodes=graph.size();
//     vector<bool>visited(numNodes,false);

//     #pragma omp parallel for shared(visited)
//     for(int i=0;i<numNodes;i++)
//       {
//         if(!visited[i]){
//             stack<int>stack;

//             #pragma omp critical
//             {
//                 if(!visited[i]){
//                     stack.push(i);
//                     visited[i]=true;
//                 }
//             }

//             while(!stack.empty()){
//                 int currentnode=stack.top();
//                 stack.pop();

//                 cout<<"Visited :- "<<currentnode<<endl;

//                 #pragma omp critical
//                 {
//                     for(int neighbor:graph[currentnode]){
//                         if(!visited[neighbor]){
//                             stack.push(neighbor);
//                             visited[neighbor]=true;
//                         }
//                     }

//                 }
//             }
//         }
//       }
    
// }

// int main() {
//     std::vector<std::vector<int>> graph = {
//         {1, 2},       // 0
//         {0, 3, 4},    // 1
//         {0, 4},       // 2
//         {1, 5},       // 3
//         {1, 2, 5},    // 4
//         {3, 4}        // 5
//     };

//     parallelDFS(graph, 0);
// }



#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

void parallelBFS(const std::vector<std::vector<int>>& graph, int startVertex) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> queue;

    // Start by visiting the start vertex
    visited[startVertex] = true;
    queue.push(startVertex);

    // BFS process
    while (!queue.empty()) {
        int currentSize = queue.size();
        
        // Process each level in parallel
        #pragma omp parallel for shared(visited, queue)
        for (int i = 0; i < currentSize; i++) {
            int u;
            #pragma omp critical
            {
                u = queue.front();
                queue.pop();
            }

            std::cout << "Visited " << u << " by thread " << omp_get_thread_num() << std::endl;

            // Check all adjacent vertices
            for (int v : graph[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    #pragma omp critical
                    queue.push(v);
                }
            }
        }
    }
}

int main() {
    // Example graph represented as an adjacency list
    std::vector<std::vector<int>> graph = {
        {1, 2},    // Vertex 0 is connected to vertices 1 and 2
        {0, 3, 4}, // Vertex 1 is connected to vertices 0, 3, and 4
        {0, 4},    // Vertex 2 is connected to vertices 0 and 4
        {1, 5},    // Vertex 3 is connected to vertices 1 and 5
        {1, 2, 5}, // Vertex 4 is connected to vertices 1, 2, and 5
        {3, 4}     //
    };
    parallelBFS(graph,0);
}

