//
//  baseline.h
//  igs
//
//  Created by Bowen Li on 2/16/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef BASELINE_H
#define BASELINE_H

#include<vector>
#include<string>
#include <typeinfo>


#include"../node/node.h"
#include "../label/string_label.h"

using Label=label::StringLabel;
using Node=node::Node<Label>;

namespace baseline{



void Topdown(Node &root, Node& target, int ** oracle,bool & found,int &step);
bool Reachability(Node& start,Node& target,int ** tree_oracle);





bool Reachability(Node& start,Node& target,int** oracle){
    
   // std::cout<<"checking: "<<start.id()<<"-->"<<target.id()<<std::endl;
//    <<" target id: "<target.id()<<std::endl;
    if(oracle[start.id()-1][target.id()-1]==1)
        return true;
    
    return false;

}




void Topdown(Node &root, Node& target, int** oracle,bool &found,int& step){
        
    bool child_reach_target=0;
    //std::cout<<"root node: "<<root.id()<<" found: "<<found <<std::endl;
    
    //
    if(Reachability(root, target, oracle)==true){
       for(auto child:root.get_children()){
          if(found==0){
              step++;
              if(Reachability(child, target, oracle)==true){
                  child_reach_target=1;
                  Topdown(child, target, oracle, found, step);
              }
              
              
          }
           
           
       }
      if(child_reach_target==0){
          found=true;
          target.setDepth(root.depth());
      }
      
    }
}




}


#endif /* baseline_h */
