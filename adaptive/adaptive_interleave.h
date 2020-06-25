//
//  adaptive_interleave.h
//  adaptive
//
//  Created by Bowen Li on 3/30/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef adaptive_interleave_h
#define adaptive_interleave_h

#include "../node/node.h"
#include "../label/string_label.h"
#include "../other/bfunction.h"
#include "../heavy_tree/supernode.h"
#include "../heavy_tree/path_tree_generator.h"
#include "../ordered_interleave/interleave_ordered.h"

#include <vector>
#include <utility>
#include <algorithm>
#include <typeinfo>

namespace  adaptive_interleave{

using Label=label::StringLabel;
using Node=node::Node<Label>;
using Supernode=supernode::Supernode;

int Adaptive_interleave(Node& target,Node& root,int** oracle,Supernode * sroot, bool& found, int& steps,int thre);
int check_children_reachablity(Node & node, Node& target,int** oracle, int& steps);

int Adaptive_interleave(Node& target,Node& root,int** oracle,Supernode * sroot, bool& found, int& steps,int thre){
    
    // std::cout<<"root: "<<root.id()<<std::endl;
    // std::cout<<"supernode: "<<std::endl;
    // sroot->print_all_nodes();
    //std::cout<<"steps before check child: "<<steps<<std::endl;
    int target_pos=check_children_reachablity(root, target, oracle, steps);
    // std::cout<<"steps after check child: "<<steps<<std::endl;
    // std::cout<<"targer pos: "<<target_pos<<std::endl;
    if(target_pos==-1){
        target.setDepth(root.depth());
        found=true;
    }
    if(!found){
        int fixed_dgree=thre;
        if((int)root.get_children()[target_pos].children_count()>fixed_dgree){
            //std::cout<<"bfs"<<std::endl;
            //int bfs_pos;
            if(ordered_interleave::node_in_snode(root.get_children()[target_pos].id(), sroot))
                Adaptive_interleave(target, root.get_nonconst_children()[target_pos], oracle, sroot, found, steps,thre);
            else{
                for(auto& schild: sroot->getChildren())
                    if(ordered_interleave::node_in_snode(root.get_children()[target_pos].id(), schild))
                        Adaptive_interleave(target, root.get_nonconst_children()[target_pos], oracle, schild, found, steps,thre);
            }
        }
        else{
            //std::cout<<"dfs"<<std::endl;
            int index;
            // std::cout<<"steps before dfs binary search: "<<steps<<std::endl;
            // //index=ordered_interleave::binary_search_supernode(sroot, target, oracle, steps);
            // std::cout<<"steps after dfs binary search: "<<steps<<std::endl;
            //std::cout<<"dfs node: "<<root.get_children()[target_pos].id()<<std::endl;
            if(ordered_interleave::node_in_snode(root.get_children()[target_pos].id(), sroot)){
                index=ordered_interleave::binary_search_supernode(sroot, target, oracle,steps);
                Adaptive_interleave(target, *(sroot->get_nonconst_Nodes()[index]), oracle, sroot, found, steps,thre);
            }
            else{
                for(auto& schild: sroot->getChildren()){
                    if(ordered_interleave::node_in_snode(root.get_children()[target_pos].id(), schild)){
                    //std::cout<<"super node: "<<std::endl;
                    //schild->print_all_nodes();
                    index=ordered_interleave::binary_search_supernode(schild, target, oracle,steps);
                    //std::cout<<"index: "<<index<<std::endl;
                    Adaptive_interleave(target,*(schild->get_nonconst_Nodes()[index]) , oracle, schild, found, steps,thre);
                    }
                }
            }
        }
    }
    
    return steps;
}


int check_children_reachablity(Node & node, Node& target,int** oracle, int& steps){
    //std::cout<<"checking"<<std::endl;
    int target_pos=-1;
    
    
    std::vector<std::pair<int, int>> sort_vector;
    int pos=0;
    if((int)node.children_count()>1){
        for(auto& child: node.get_children()){
            sort_vector.push_back(std::make_pair(pos, (int)child.get_tree_size()));
            pos++;
        }
        std::sort(sort_vector.begin(),sort_vector.end(),ordered_interleave::nodes_sort);
    }
    
    if(node.children_count()==1){
        steps++;
        if(ordered_interleave::Reachability(node.get_children()[0].id(), target.id(), oracle))
            target_pos=0;
    }
    else{
        for(int i=0;i<(int)sort_vector.size();i++){
            int node_id=node.get_children()[sort_vector[i].first].id();
            //std::cout<<"node id:"<<node_id<<std::endl;
            if(ordered_interleave::Reachability(node_id, target.id(), oracle)){
                   target_pos=sort_vector[i].first;
                   break;
            }
            else
                steps++;
        }
    }

    return target_pos;
}








}




#endif /* adaptive_interleave_h */
