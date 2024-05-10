#include "GraphReaderAlt.h"


    /* We never use the second parameter ?? */
std::pair<int, int> GraphReaderAlt::getVertexIdx(Graph &G, std::string vname){
    for(int i = 0; i < G.n; i++)
        if(G.partA[i].id_ == vname)
            return {i, 0};
        
    for(int i = 0; i < G.m; i++)
        if(G.partP[i].id_ == vname)
            return {i, 1};

    return {-1, -1};
}

void GraphReaderAlt::readParititions(Graph &G){
    std::cin >> G.n;
    G.partA.resize(G.n);
    for(int i = 0; i < G.n; i++)
        std::cin >> G.partA[i].id_ >> G.partA[i].upper_quota_;
    
    std::cin >> G.m;
    G.partP.resize(G.m);
    for(int i = 0; i < G.m; i++)
        std::cin >> G.partP[i].id_ >> G.partP[i].upper_quota_;
}

void GraphReaderAlt::readEdges(Graph &G){
    std::cin >> G.k;
    G.edges.resize(G.k+1);
    for(int i = 1; i <= G.k; i++){
        int l;
        std::cin >> l;
        G.edges[i].resize(l);
        for(int j = 0; j < l; j++)
            std::cin >> G.edges[i][j].id1 >> G.edges[i][j].id2;
    }
}

void GraphReaderAlt::fillVAdj(Graph &G){
    for(int i = 1; i <= G.k; i++){
        for(int j = 0; j < G.edges[i].size(); j++){
            int idx1 = getVertexIdx(G, G.edges[i][j].id1).first, idx2 = getVertexIdx(G, G.edges[i][j].id2).first;
            if(idx1 == -1 || idx2 == -1) continue;
            G.partA[idx1].adj_list.push_back(G.edges[i][j].id2);
            G.partP[idx2].adj_list.push_back(G.edges[i][j].id1);
        }
    }
}

void GraphReaderAlt::readClassification(Graph &G, int idx, bool A){
    ClassificationListElement c;
    std::cin >> c.id_ >> c.upper_quota_ >> c.num_vertices;
    c.vertices.resize(c.num_vertices);

    for (int k = 0; k < c.num_vertices; k++) 
        std::cin >> c.vertices[k];
    
    if(A) G.partA[idx].classifications.add_element(c);
    else G.partP[idx].classifications.add_element(c);
}

void GraphReaderAlt::readClassifications(Graph &G){
    for (int i = 0; i < G.n + G.m; i++){
        std::string vname;
        int noClassifications;
        std::cin >> vname >> noClassifications;

        int idx = getVertexIdx(G, vname).first, part = getVertexIdx(G, vname).second;

        if (idx == -1) continue; // vertex not found

        for (int j = 0; j < noClassifications; j++)
            if (part == 0)
                readClassification(G, idx, true);
            else
                readClassification(G, idx, false);
    }
}


Graph GraphReaderAlt::read_graph(){
    Graph G;
    readParititions(G);
    readEdges(G);
    fillVAdj(G);
    readClassifications(G);
    return G; // pass by value
}


