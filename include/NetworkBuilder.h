#ifndef NETWORK_BUILDER_H
#define NETWORK_BUILDER_H

#include "GraphDefs.h"
#include "Vertex.h"
#include <iostream>
#include <utility>
#include <string>
#include <limits.h>
#include <algorithm>

class NetworkBuilder{
    private:

    std::pair<int, int> getVertexIdx(Graph &G, std::string vname);

    // Fix this into shorter code & can shift this to the Graph Reader 
    void addFundamenalClasses(Graph &G, int idx, bool isA);

    // This is useless 
    void sortClassifications(std::vector<Vertex> &part, int idx);
    
    void enumerateClassifications(std::vector<Vertex> &part, int idx);

    std::vector<int> initialiseRoots(ClassificationList &classifications, std::vector<bool> &usedClassification, int &usedClassifications);

    int findSmallestUnusedIdx(ClassificationList &classifications, std::vector<bool> &usedClassification);

    // Use pass by reference ??
    bool violatingClassifications(ClassificationListElement c1, ClassificationListElement c2);

    // Use pass by reference ??
    bool isChild(ClassificationListElement c1, ClassificationListElement c2);

    // Use pass by reference and return everything instead of just exiting ??
    void isNonLaminar(ClassificationListElement c, std::vector<int> roots, ClassificationList classifications);

    std::vector<int> findChildren(ClassificationList classifications, ClassificationListElement c, std::vector<int> roots);

    void addChildren(int parent, int child, std::vector<std::vector<TreeNode>> &tree, ClassificationList classifications);

    std::vector<int> updateRoots(std::vector<int> roots, std::vector<int> children, int smallestUnusedIdx);

    void buildClassificationTree(std::vector<Vertex> &part, int idx);

    void reenumerateTree(Vertex &v, int &offset);

    int reenumerateVertices(Graph &G);

    void initialiseNetwork(Graph &G, int numNodes);

    public:

    void initBuild(Graph &G);

    void buildNetwork(Graph &G);
};



#endif