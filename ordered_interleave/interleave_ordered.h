

#ifndef interleave_ordered_h
#define interleave_ordered_h

#include "../node/node.h"
#include "../heavy_tree/supernode.h"
#include "../label/string_label.h"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

namespace ordered_interleave {

using Label=label::StringLabel;
using Node=node::Node<Label>;
using Supernode=supernode::Supernode;


int Ordered_Interleave(const Node &root, Supernode* sroot,Node& target,int** oracle,bool&found,int& steps);
int binary_search_supernode(Supernode* supernode, Node& target,int** oracle,int &step);
int binary_search_supernode_recurion(Supernode* supernode,int node_id, int** oracle,int begin,int end,int &step);
bool Reachability(int start_id,int target_id,int** oracle);
bool node_in_snode(int node_id,Supernode* snode);
bool nodes_sort (const std::pair<int, int>& i,const std::pair<int, int>& j);

int Ordered_Interleave(const Node &root, Supernode* sroot,Node& target,int** oracle,bool&found, int& steps){
     
   // std::cout<<"root: "<<root.id()<<std::endl;
   // std::cout<<"super node: "<<std::endl;
   // sroot->print_all_nodes();
    if(found==false){
        int index;
        index=binary_search_supernode(sroot, target, oracle,steps);
        bool child_flag=false;
        //std::cout<<"binary search find node: "<<sroot->getNodes()[index]->id()<<std::endl;
        //std::cout<<"steps after binary search: "<<steps<<std::endl;
        std::vector<std::pair<int, int>> sort_vector;
        for(int i=0;i<(int)sroot->getNodes()[index]->get_children().size();i++){
            //std::cout<<"child: "<<sroot->getNodes()[index]->get_children()[i].id()<<std::endl;
            int pos=i;
            int subtree_size=(int)sroot->getNodes()[index]->get_children()[i].get_tree_size();
            sort_vector.push_back(std::make_pair(pos,subtree_size));
        }
        // for(auto i: sort_vector)
        //     std::cout<<"node pos: "<<i.first<<"id: "<<sroot->getNodes()[index]->get_children()[i.first].id()<<"size: "<<i.second<<std::endl;
        int target_pos=-1;
        std::sort(sort_vector.begin(),sort_vector.end(),nodes_sort);
        for(int i=0;i<(int)sort_vector.size();i++){
            int pos=sort_vector[i].first;
            //std::cout<<"child: "<<sroot->getNodes()[index]->get_children()[pos].id()<<std::endl;
             if(!node_in_snode(sroot->getNodes()[index]->get_children()[pos].id(), sroot)){
                if(Reachability(sroot->getNodes()[index]->get_children()[pos].id(), target.id(), oracle)){
                     child_flag=true;
                     target_pos=pos;
                     break;
                }
                else
                    steps++;

             }
        }

         if(child_flag==false){

            //std::cout<<"find target: "<<sroot->getNodes()[index]->id()<<std::endl;
            target.setDepth(sroot->getNodes()[index]->depth());
            found=true;

        }
        else{
            for(auto& schild: sroot->getChildren()){
                if(node_in_snode(sroot->getNodes()[index]->get_children()[target_pos].id(), schild))
                    Ordered_Interleave(sroot->getNodes()[index]->get_children()[target_pos], schild, target, oracle,found,steps);
            }
        }
    }

     
    return steps;
 }
     
     
     
int binary_search_supernode(Supernode* supernode, Node& target,int** oracle,int& step){
    
    int begin=0;
    int end=(int)supernode->nodes_count()-1;
    int node_id=target.id();
    //std::cout<<"end index: "<<end<<std::endl;
    //std::cout<<"traget id: "<<node_id<<std::endl;
    
    
    int index=binary_search_supernode_recurion(supernode, node_id, oracle,begin,end,step);
    //std::cout<<"index: "<<index<<std::endl;
    //std::cout<<"steps: "<<step<<std::endl;
    
    return index;
}
     
     
     
int binary_search_supernode_recurion(Supernode* supernode,int target_id, int** oracle,int begin,int end,int &step){
    
    int index=-1;
    //basecase:
    if(end==begin){
        //std::cout<<"one element"<<std::endl;
        step++;
        if(Reachability(supernode->getNodes()[begin]->id(), target_id, oracle))
            return begin;
        else
            return -1;
    }
    int mid_index=begin+(end-begin)/2;
    //std::cout<<"mid index: "<<mid_index<<std::endl;
    int start_id=supernode->getNodes()[mid_index]->id();
    step++;
    if(Reachability(start_id, target_id, oracle)==true){
        //std::cout<<"mid can reach"<<std::endl;
        index=mid_index;
        int new_begin=mid_index+1;
        if(new_begin>end)
            new_begin=end;
        int right_index=binary_search_supernode_recurion(supernode, target_id, oracle,mid_index+1, end,step);
        //std::cout<<"right index: "<<right_index<<" begin: "<<mid_index+1<<" end: "<<end<<std::endl;
        if(right_index!=-1)
            index=right_index;
    }
    else{
        //std::cout<<"mid cannot reach"<<std::endl;
        if(mid_index==begin)
            return -1;
//        std::cout<<"begin: "
//        int new_end=mid_index-1;
//        if(new_end<begin)
//            new_end=begin;
        int left_index=binary_search_supernode_recurion(supernode, target_id, oracle, begin, mid_index-1,step);
        index=left_index;
    }
    
    
    return index;
    
    
}

bool Reachability(int start_id,int target_id,int** oracle){
     
    //std::cout<<start_id<<"-->"<<target_id<<std::endl;
    if(oracle[start_id-1][target_id-1]==1)
        return true;
    
    return false;

}
    
    

bool node_in_snode(int node_id,Supernode* snode){
    bool flag=false;
    for(auto& node:snode->getNodes()){
        //std::cout<<"compare: "<<node_id<<"-->"<<node->id()<<std::endl;
        if(node->id()==node_id)
            flag=true;
    }
    
    
   return flag;
    
    
}

bool nodes_sort (const std::pair<int, int>& i,const std::pair<int, int>& j)
{
   return i.second > j.second;
    
}



}




#endif /* interleave_ordered_h */
