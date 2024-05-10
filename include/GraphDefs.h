#ifndef GRAPH_DEFS_H
#define GRAPH_DEFS_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "TDefs.h"


// class VertexAlt;
class TreeNode;
class Edge;
class Graph;
class GraphReaderAlt;
class NetworkBuilder;
class Algorithm;
struct Tree;
struct TreeNode;

/* To add a new Class Named This*/
struct TreeNode{
    int vertex; // Change this name to node_id
    int upper_quota_;
    int lower_quota_;


    TreeNode(int a, int b): vertex(a), upper_quota_(b) {}
    TreeNode(int a, int b, int c): vertex(a), lower_quota_(b), upper_quota_(c) {}
};


/* Use this in the class Vertex*/
struct Tree{
    int classificationTreeRoot; // RootId
    std::vector<std::vector<TreeNode>> classificationTreeChildren; // (child, quota)
    std::map<std::string, int> classificationIdx; // Node Id
    std::map<int, std::string> classificationName; // Node Id
};

struct Edge{
    IdType id1;
    IdType id2;
};

/* Add a new module called Graphs*/
class Graph{
    int n, m, k; // # vertices in partition A, P, # edge ranks
    /* Can we use map<IdTypeAlt, VertexPtr> for partitions??*/
    std::vector<Vertex> partA, partP;
    std::vector<std::vector<Edge>> edges;
    std::vector<std::vector<int>> network; // adjacency matrix of residual network

    public:
        friend class GraphReaderAlt;
        friend class NetworkBuilder;
        friend class Algorithm;

        void printNetwork();
        void printEdges();
};

#endif
