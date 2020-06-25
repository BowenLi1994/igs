//
//  supernode_impl.h
//  tree_interleave
//
//  Created by Bowen Li on 3/3/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef supernode_impl_h
#define supernode_impl_h


int Supernode::id(){
    return id_;
}

const std::vector<Node>& Supernode::getNodes() const{
    
    return nodes_;
}


const std::vector<Supernode>& Supernode::getChildren() const{
    
    return children_;
}
//
//
const Supernode::SizeType Supernode::children_count() const{
    
    return children_.size();
}
//
//
Supernode& Supernode::add_child(Supernode child){
    children_.push_back(child);
    
    return children_.back();
        
}
//
const Supernode::SizeType Supernode::nodes_count() const{

    return nodes_.size();
}

Node& Supernode::add_node(Node node){
    
    nodes_.push_back(node);
    
    return nodes_.back();
        
}
//
int Supernode::get_heavy_tree_size() const{
    
    int size = 1;
    for (const auto& child: children_) {
        size += child.get_heavy_tree_size();
    }
    return size;
    
}


void Supernode::print_all_nodes(){
    for(auto node: nodes_)
        std::cout<<"node: "<<node.id()<<std::endl;
}

#endif /* supernode_impl_h */
