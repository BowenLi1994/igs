//
//  supernode.h
//  tree_interleave
//
//  Created by Bowen Li on 3/3/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef supernode_h
#define supernode_h

#include "../node/node.h"
#include "../label/string_label.h"
#include <vector>

namespace supernode{

    using Node=node::Node<label::StringLabel>;

class Supernode{
public:
    using SizeType = typename std::vector<Node>::size_type;
public:
    
    int id();
    const std::vector<Node *> getNodes() const ;
    std::vector<Node *> get_nonconst_Nodes();
    const std::vector<Supernode *> getChildren() const;
    std::vector<Supernode *> get_nonconst_Children();
    const SizeType children_count() const;
    void add_child(Supernode* child);
    int get_heavy_tree_size() const;
    
    const SizeType nodes_count() const;
    void add_node(Node* node);
    
    void print_all_nodes();
    
    
    private:
    int id_;
    std::vector<Node *> nodes_;
    std::vector<Supernode *> children_;
    
    

};

#include "supernode_impl.h"
}



#endif /* supernode_h */
