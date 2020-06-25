//
//  interleave.h
//  tree_interleave
//
//  Created by Bowen Li on 3/4/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef interleave_h
#define interleave_h

#include "../node/node.h"
#include "../heavy_tree/supernode.h"
#include "../label/string_label.h"


namespace interleave {

using Label=label::StringLabel;
using Node=node::Node<Label>;
using Supernode=supernode::Supernode;


int Interleave(const Node &root, Supernode* sroot,Node& target,int** oracle,bool& found);
int binary_search_supernode(Supernode* supernode, Node& target,int** oracle,int &step);
int binary_search_supernode_recurion(Supernode* supernode,int node_id, int** oracle,int begin,int end,int &step);
bool Reachability(int start_id,int target_id,int** oracle);
bool node_in_snode(int node_id,Supernode* snode);


int Interleave(const Node &root, Supernode* sroot,Node& target,int** oracle,bool&found){
     
    int steps=0;
    if(found==false){
        int index;
        index=binary_search_supernode(sroot, target, oracle,steps);
        bool child_flag=false;
        //std::cout<<"root: "<<sroot->getNodes()[index]->id()<<std::endl;
        for(auto& child:sroot->getNodes()[index]->get_children()){
            //std::cout<<"child: "<<child.id()<<std::endl;
            if(!node_in_snode(child.id(), sroot)){
                if(Reachability(child.id(), target.id(), oracle)){
                    child_flag=true;
                    break;
                    }
                else
                    steps++;
                }
        }
        //std::cout<<"child flag: "<<child_flag<<std::endl;
        if(child_flag==false){
            found=true;
            target.setDepth(root.depth());
        }
        else{
            for(auto& child:sroot->getNodes()[index]->get_children()){
                if(node_in_snode(child.id(), sroot)==false){
                     if(Reachability(child.id(), target.id(), oracle)){
                         for(auto& schild: sroot->getChildren()){
                             if(node_in_snode(child.id(), schild))
                                 steps+=Interleave(child, schild, target, oracle,found);
                         }
                     }
                }
            }
        }
        
        
        
//        else{
//            for(auto& child:sroot->getNodes()[index]->get_children()){
//                if(node_in_snode(child.id(), sroot)==false){
//                    if(Reachability(child.id(), target.id(), oracle)){
//                        for(auto& schild: sroot->getChildren()){
//                            if(node_in_snode(child.id(), schild))
//                                steps+=Interleave(child, schild, target, oracle,found);
//                        }
//                    }
//                    else
//                        steps++;
//
//                }
//            }
//        }
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
    for(auto& node:snode->getNodes())
        if(node->id()==node_id)
            flag=true;
    
    
   return flag;
    
    
}


}
#endif /* interleave_h */
