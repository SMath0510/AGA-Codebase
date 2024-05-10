#include "Algorithm.h"
#include "GraphDefs.h"

std::pair<int, int> Algorithm::getVertexIdx(Graph &G, std::string vname){
    for(int i = 0; i < G.n; i++)
        if(G.partA[i].get_id() == vname)
            return {i, 0};
        
    for(int i = 0; i < G.m; i++)
        if(G.partP[i].get_id() == vname)
            return {i, 1};

    return {-1, -1};
}

void Algorithm::addEdge(Graph &G, Edge edge){
    int u = getVertexIdx(G, edge.id1).first, v = getVertexIdx(G, edge.id2).first;
    if (u == -1 || v == -1) return;
    int LIdx = G.partA[u].classification_tree.classificationIdx["C0" + std::to_string(u) + "_" + std::to_string(v)];
    int RIdx = G.partP[v].classification_tree.classificationIdx["C1" + std::to_string(v) + "_" + std::to_string(u)];
    G.network[LIdx][RIdx] = 1;
}

void Algorithm::addEdges(Graph &G, int rank){
    for (auto edge : G.edges[rank])
        addEdge(G, edge);
}

void Algorithm::maxFlow(Graph &G, int rank){
    int s = 0, t = 1;
    int maxFlow = 0;
    while (true){
        // BFS to find augmenting path
        std::vector<int> parent(G.network.size(), -1);
        std::queue<int> q;
        q.push(s);
        while (!q.empty()){
            int u = q.front();
            q.pop();
            for (int v = 0; v < G.network.size(); v++){
                if (parent[v] == -1 && G.network[u][v] > 0){
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        if (parent[t] == -1) break; // no augmenting path found

        // find path flow
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v]){
            int u = parent[v];
            pathFlow = std::min(pathFlow, G.network[u][v]);
        }

        // augment path flow
        for (int v = t; v != s; v = parent[v]){
            int u = parent[v];
            G.network[u][v] -= pathFlow;
            G.network[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    std::cout << maxFlow << " edges of rank " << rank << " added to matching\n";
}

std::vector<bool> Algorithm::inSk(Graph &G){
    std::vector<bool> inSk(G.network.size(), false);
    std::queue<int> q;
    q.push(0);
    inSk[0] = true;
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int v = 0; v < G.network.size(); v++){
            if (!inSk[v] && G.network[u][v] > 0){
                inSk[v] = true;
                q.push(v);
            }
        }
    }
    return inSk;
}

std::vector<bool> Algorithm::inTk(Graph &G){
    std::vector<bool> inTk(G.network.size(), false);
    std::queue<int> q;
    q.push(1);
    inTk[1] = true;
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int v = 0; v < G.network.size(); v++){
            if (!inTk[v] && G.network[v][u] > 0){
                inTk[v] = true;
                q.push(v);
            }
        }
    }
    return inTk;
}

void Algorithm::deleteReverseMinCutEdges(Graph &G, std::vector<bool> inS){
    for (int i = 0; i < G.network.size(); i++)
        for (int j = 0; j < G.network.size(); j++)
            if (inS[i] && !inS[j] && G.network[i][j] > 0)
                G.network[i][j] = 0;
}

void Algorithm::printNetwork(Graph &G){
    int numNodes = G.network.size();
    std::cout << "x\t";
    for (int i = 0; i < numNodes; i++)
        std::cout << i << "\t";
    std::cout << "\n";
    for (int i = 0; i < numNodes; i++){
        std::cout << i << "\t";
        for (int j = 0; j < numNodes; j++)
            std::cout << G.network[i][j] << "\t";
        std::cout << "\n";
    }
}

void Algorithm::deleteUnwatedLREdges(Graph &G, std::vector<bool> inS, std::vector<bool> inT, int i){
    for (int j = i + 1; j <= G.k; j++){
        std::vector<Edge> edgesToKeep;
        for (auto edge : G.edges[j]){
            int u = getVertexIdx(G, edge.id1).first, v = getVertexIdx(G, edge.id2).first;
            if (u == -1 || v == -1) continue;
            int LIdx = G.partA[u].classification_tree.classificationIdx["C0" + std::to_string(u) + "_" + std::to_string(v)];
            int RIdx = G.partP[v].classification_tree.classificationIdx["C1" + std::to_string(v) + "_" + std::to_string(u)];

            if (inS[LIdx] && inT[RIdx])
                edgesToKeep.push_back(edge);
        }
        G.edges[j] = edgesToKeep;
    }
}

void Algorithm::printMatching(Graph &G, int rank){
    std::cout << "Current Matching:\n";
    for (int i = 1; i <= rank; i++){
        std::cout << "Rank " << i << ":\n";
        for (auto edge : G.edges[i]){
            int u = getVertexIdx(G, edge.id1).first, v = getVertexIdx(G, edge.id2).first;
            if (u == -1 || v == -1) continue;
            int LIdx = G.partA[u].classification_tree.classificationIdx["C0" + std::to_string(u) + "_" + std::to_string(v)];
            int RIdx = G.partP[v].classification_tree.classificationIdx["C1" + std::to_string(v) + "_" + std::to_string(u)];
            if (G.network[LIdx][RIdx] == 0)
                std::cout << "(" << edge.id1 << ", " << edge.id2 << "), ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Algorithm::printClassifications(Vertex v){
    std::cout << v.get_id() << ": " << v.get_upper_quota() << "\n";
    for (int i = 0; i < v.classifications.size(); i++){
        std::cout << v.classifications[i].id_ << " " << v.classifications[i].upper_quota_ << " " << v.classifications[i].num_vertices << "\n";
        for (auto vertex : v.classifications[i].vertices)
            std::cout << vertex << " ";
        std::cout << "\n\n";
    }
}

void Algorithm::printClassificationIdx(Vertex &v){
    std::cout << v.id_ << ": " << v.upper_quota_ << "\n";
    for (auto it : v.classification_tree.classificationIdx)
        std::cout << it.first << " " << it.second << "\n";
}



void Algorithm::printClassificationIdxs(Graph &G){
    for (int i = 0; i < G.n; i++)
        printClassificationIdx(G.partA[i]);
    for (int i = 0; i < G.m; i++)
        printClassificationIdx(G.partP[i]);
}


void Algorithm::runAlgorithm(Graph &G){
    for (int i = 1; i <= G.k; i++){
        addEdges(G, i);
        // G.printNetwork();
        maxFlow(G, i);
        std::vector<bool> inS = inSk(G), inT = inTk(G); // S, T, U decomposition
        deleteReverseMinCutEdges(G, inS);
        deleteUnwatedLREdges(G, inS, inT, i);
        printMatching(G, i);
        // G.printNetwork();
    }
}