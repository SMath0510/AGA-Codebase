#ifndef GRAPH_READER_ALT_H
#define GRAPH_READER_ALT_H

#include "GraphDefs.h"
#include "Vertex.h"

#include <utility>
#include <iostream>

class GraphReaderAlt{

    /* We never use the second parameter ?? */
    std::pair<int, int> getVertexIdx(Graph &G, std::string vname);

    void readParititions(Graph &G);

    void readEdges(Graph &G);

    void fillVAdj(Graph &G);
    
    void readClassification(Graph &G, int idx, bool A);

    void readClassifications(Graph &G);

    public:

    Graph read_graph();
};

#endif

