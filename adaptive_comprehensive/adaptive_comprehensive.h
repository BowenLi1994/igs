//
//  adaptive_comprehensize.h
//  adaptive_comprehensive
//
//  Created by Bowen Li on 4/12/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef adaptive_comprehensize_h
#define adaptive_comprehensize_h

#include <map>
#include "../adaptive_sibling/adaptive_sbling.h"
namespace adptive_comprehensive_interleave {


using Label=label::StringLabel;
using Node=node::Node<Label>;
using Supernode=supernode::Supernode;

struct tree_parameter{
    
    int tree_size;
    int tree_fanout;
    int tree_path;
    
};


struct tree_parameter tree_analyse(Node& node);
int Adaptive_comprehensive_interleave(Node& target,Node& root,int** oracle,Supernode * sroot, bool& found, int& steps,int thre);
void get_depth_recusive(const Node& node, std::vector<int>& depth);


int Adaptive_comprehensive_interleave(Node& target,Node& root,int** oracle,Supernode * sroot, bool& found, int& steps,int thre){
    
    
    
 
    
    
    int target_pos=adaptive_sibling_interleave::check_children_reachablity(root, target, oracle, steps);
    if(target_pos==-1){
          target.setDepth(root.depth());
          found=true;
    }

    
    
    
    if(!found){
        
         struct tree_parameter result;
         result=tree_analyse(root);
         double comprhensive_threshold=(double)thre;
         double tree_threshold=0.1*(double)(result.tree_size*result.tree_fanout)/double(result.tree_path+1);
        if(tree_threshold>comprhensive_threshold){
            
              if(ordered_interleave::node_in_snode(root.get_children()[target_pos].id(), sroot))
                  Adaptive_comprehensive_interleave(target, root.get_nonconst_children()[target_pos], oracle, sroot, found, steps,thre);
              else{
                  for(auto& schild: sroot->getChildren())
                      if(ordered_interleave::node_in_snode(root.get_children()[target_pos].id(), schild))
                          Adaptive_comprehensive_interleave(target, root.get_nonconst_children()[target_pos], oracle, schild, found, steps,thre);
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
                  Adaptive_comprehensive_interleave(target, *(sroot->get_nonconst_Nodes()[index]), oracle, sroot, found, steps,thre);
              }
              else{
                  for(auto& schild: sroot->getChildren()){
                      if(ordered_interleave::node_in_snode(root.get_children()[target_pos].id(), schild)){
                      //std::cout<<"super node: "<<std::endl;
                      //schild->print_all_nodes();
                      index=ordered_interleave::binary_search_supernode(schild, target, oracle,steps);
                      //std::cout<<"index: "<<index<<std::endl;
                      Adaptive_comprehensive_interleave(target,*(schild->get_nonconst_Nodes()[index]) , oracle, schild, found, steps,thre);
                      }
                  }
              }
          }
      }
      
      return steps;
    
    
}


struct tree_parameter tree_analyse(Node& node){
    struct tree_parameter result;
    std::vector<int> depth_set;
    get_depth_recusive(node, depth_set);
//    for(auto depth:depth_set){
//        std::cout<<"node depth: "<<depth<<std::endl;
//    }
    std::map<int, int> depth_map;
    //int max_depth;
    
    for(auto depth : depth_set){
        std::map<int,int>::iterator it;
        it=depth_map.find(depth);
        if(it!=depth_map.end()){
            it->second++;
        }
        else{
            depth_map.emplace(depth, 1);
        }
    }
    
    int size_temp;
    int path_temp;
    int width_temp;
    
    if(depth_map.size()==0){
        size_temp=path_temp=width_temp=0;
    }
    else if(depth_map.size()==1){
        size_temp=1;
        path_temp=1;
        width_temp=1;
    }
    else{
        size_temp=node.get_tree_size();
        path_temp=depth_map.end()->first-depth_map.begin()->first+1;
        int max_value=0;
        for(auto pair :depth_map){
            if(pair.second>max_value)
                max_value=pair.second;
        }
        width_temp=max_value;
        

    }
    
    result.tree_fanout=width_temp;
    result.tree_path=path_temp;
    result.tree_size=size_temp;
    
    
    return result;
}

void get_depth_recusive(const Node& node, std::vector<int>& depth){
    
    depth.push_back(node.depth());
    for(const auto& child: node.get_children()){
        get_depth_recusive(child, depth);
    }
}






}




#endif /* adaptive_comprehensize_h */
