#include "GraphDefs.h"
#include<iostream>

void Graph::printNetwork(){
    for(int i = 0; i < network.size(); i++){
        for(int j = 0; j < network[i].size(); j++)
            std::cout << network[i][j] << " ";
        std::cout << std::endl;
    }
}
void Graph::printEdges(){
    for(int i = 1; i <= k; i++){
        std::cout << "Rank " << i << ":\n";
        for(int j = 0; j < edges[i].size(); j++)
            std::cout << edges[i][j].id1 << " " << edges[i][j].id2 << std::endl;
    }
}