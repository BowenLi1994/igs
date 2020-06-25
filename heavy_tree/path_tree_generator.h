//
//  path_tree_generator.h
//  tree_interleave
//
//  Created by Bowen Li on 3/4/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef path_tree_generator_h
#define path_tree_generator_h


#include "../node/node.h"
#include "../label/string_label.h"
#include "supernode.h"

namespace path_tree_generator {

using Label=label::StringLabel;
using Node=node::Node<label::StringLabel>;
using Supernode= supernode::Supernode;

void single_path_tree_generator(Node& root,std::vector<Supernode *>& tree_paths,int** oracle);
void first_time_tag(Node& node,std::vector<int>& heavy_id);
void second_time_retrive(Node& node,std::vector<int>& heavy_id,std::vector<Supernode *>& tree_paths);
void generate_path(Node&node,Supernode* snode);
void third_time_link(std::vector<Supernode *>& tree_paths,int** oracle);
bool Reachability(int start,int target,int** oracle);
bool check_supernode_link(Supernode* snode1,Supernode* snode2,int ** oracle);

void heavy_path_trees_collection_generator(std::vector<Node>& trees_collection, std::vector<Supernode* >& Supernodes_collection, std::vector<int **>& trees_oracle);


void single_path_tree_generator(Node& root,std::vector<Supernode *>& tree_paths,int** oracle){
    
     std::vector<int> heavy_id;
     first_time_tag(root, heavy_id);
//     for(auto i: heavy_id)
//         std::cout<<i<<std::endl;
     second_time_retrive(root, heavy_id,tree_paths);

    
    third_time_link(tree_paths, oracle);
    
//        int counter=1;
//         for(auto path:tree_paths){
//             std::cout<<"path: "<<counter<<std::endl;
//             std::cout<<path->nodes_count()<<std::endl;
//             for(auto node: path->getNodes())
//                 std::cout<<node->id()<<" ";
//             std::cout<<std::endl;
//             std::cout<<"number of children: "<<path->children_count()<<std::endl;
//             counter++;
//         }
}

void first_time_tag(Node& node,std::vector<int>& heavy_id){
    
    if(node.is_leaf())
        return;
    
    int max_degree=0;
    int max_index=0;
//    //bool
    for(int i=0;i<(int)node.children_count();i++){
        int subtree_size=node.get_children()[i].get_tree_size();
        if(subtree_size>max_degree){
            max_degree=subtree_size;
            max_index=i;
        }
    }
    //std::cout<<"node: "<<node.id()<<" heavy node: "<<node.get_children()[max_index].id()<<std::endl;
    heavy_id.push_back(node.get_children()[max_index].id());
    for(auto& child:node.get_nonconst_children())
        first_time_tag(child, heavy_id);
    

}


void second_time_retrive(Node& node,std::vector<int>& heavy_id,std::vector<Supernode *>& tree_paths){
    
    bool exsit_flag=0;
    for(auto i:heavy_id)
        if(i==node.id())
            exsit_flag=1;
    
    if(exsit_flag==0){
        //std::cout<<"begin node: "<<node.id()<<std::endl;
        Supernode* snode=new Supernode;
        generate_path(node, snode);
        tree_paths.push_back(snode);
    }
    
    for(auto& child:node.get_nonconst_children())
        second_time_retrive(child, heavy_id, tree_paths);
    
    
    
}

void generate_path(Node&node,Supernode* snode){
    snode->add_node(&node);
    int max_degree=0;
    int max_index=0;
    if(node.is_leaf())
        return;
    for(int i=0;i<(int)node.children_count();i++){
        int subtree_size=node.get_children()[i].get_tree_size();
        if(subtree_size>max_degree){
            max_degree=subtree_size;
            max_index=i;
        }
    }
    generate_path(node.get_nonconst_children()[max_index], snode);
    
}


void third_time_link(std::vector<Supernode *>& tree_paths,int** oracle){
    
    for(auto path1:tree_paths)
        for(auto path2:tree_paths)
            if(check_supernode_link(path1, path2, oracle))
                path1->add_child(path2);
}


bool Reachability(int start_id,int target_id,int** oracle){
    
  
//    <<" target id: "<target.id()<<std::endl;
    if(oracle[start_id-1][target_id-1]==1)
        return true;
    
    return false;

}



bool check_supernode_link(Supernode* snode1,Supernode* snode2,int** oracle){
    bool flag=false;
    int target_id=snode2->getNodes()[0]->id();
    
    for(auto& node: snode1->getNodes())
        for(auto& child:node->get_children())
            if(child.id()==target_id)
                flag=true;
    
    
    return flag;
}


void heavy_path_trees_collection_generator(std::vector<Node>& trees_collection, std::vector<Supernode* >& Supernodes_collection, std::vector<int **>& trees_oracle){
    
    int tree_number=(int)trees_collection.size();
    for(int i=0;i<tree_number;i++){
        
        std::vector<Supernode *> tree_paths;
        single_path_tree_generator(trees_collection[i], tree_paths, trees_oracle[i]);
        
        Supernodes_collection.push_back(tree_paths[0]);
        
        
        
        
        
        
    }
    
}


     
    
}





#endif /* path_tree_generator_h */
