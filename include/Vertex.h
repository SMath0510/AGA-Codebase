#ifndef VERTEX_H
#define VERTEX_H

#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include "TDefs.h"
#include "GraphDefs.h"
#include "PreferenceList.h"
#include "ClassificationList.h"

class Vertex {
private:
    IdType id_;                 // id of this vertex
    IdType cloned_for_id_;      // id of the vertex this was cloned for
    unsigned lower_quota_;           // least number of partners to this vertex
    unsigned upper_quota_;           // maximum number of partners to this vertex
    bool dummy_;                // is this a dummy vertex
    bool last_resort_;          // is this a last resort vertex
    int index_offset;
    std::vector<IdType> adj_list;
    ClassificationList classifications; 

    Tree classification_tree;
    PreferenceList pref_list_;  // preference list according to priority
    PreferenceList pref_list_lq_;  // preference list containing LQ vertices

public:
    explicit Vertex();
    explicit Vertex(const IdType& id);
    explicit Vertex(const IdType& id, unsigned upper_quota);
    explicit Vertex(const IdType& id, unsigned lower_quota,
                    unsigned upper_quota);
    explicit Vertex(const IdType& id, unsigned lower_quota,
                    unsigned upper_quota, bool dummy, bool last_resort);
    explicit Vertex(const IdType& id, const IdType& cloned_for_id,
                    unsigned lower_quota, unsigned upper_quota, bool dummy,
                    bool last_resort);
    virtual ~Vertex() = default;

    const IdType& get_id() const;
    const IdType& get_cloned_for_id() const;
    unsigned get_lower_quota() const;
    unsigned get_upper_quota() const;
    unsigned get_adj_list_size(); /**/
    bool is_dummy() const;
    bool is_last_resort() const;

    PreferenceList& get_preference_list();
    const PreferenceList& get_preference_list() const;

    
    PreferenceList& get_preference_list_lq();
    const PreferenceList& get_preference_list_lq() const;
    /*
    {
        classification_tree.classificationIdx[id_name] = value;
    }
    */
    friend class Algorithm; /**/
    friend class NetworkBuilder; /**/
    friend class GraphReaderAlt; /**/
};

/// print this vertex in the format v: p1, ..., pk
std::ostream& operator<<(std::ostream& out, VertexPtr v);

#endif
