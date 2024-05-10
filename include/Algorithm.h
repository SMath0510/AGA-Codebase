#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "GraphDefs.h"
#include "Vertex.h"
#include <utility>
#include <iostream>
#include <string>
#include <queue>
#include <limits.h>


class Algorithm{
    private:

    // Class Graph Shift
    std::pair<int, int> getVertexIdx(Graph &G, std::string vname);

    void addEdge(Graph &G, Edge edge);

    void addEdges(Graph &G, int rank);

    void maxFlow(Graph &G, int rank);

    std::vector<bool> inSk(Graph &G);

    std::vector<bool> inTk(Graph &G);

    void deleteReverseMinCutEdges(Graph &G, std::vector<bool> inS);

    void printNetwork(Graph &G);

    void deleteUnwatedLREdges(Graph &G, std::vector<bool> inS, std::vector<bool> inT, int i);

    void printMatching(Graph &G, int rank);

    void printClassifications(Vertex v);

    void printClassificationIdx(Vertex &v);

    void printClassificationIdxs(Graph &G);

    public:

    void runAlgorithm(Graph &G);
};

#endif