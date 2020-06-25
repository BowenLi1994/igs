//
//  analyzer.cpp
//  analyzer
//
//  Created by Bowen Li on 4/7/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "analyzer.h"
#include "../node/node.h"
#include "../label/string_label.h"
#include "../other/bfunction.h"


int main(int argc, const char * argv[]) {
    
    using Label=label::StringLabel;
    using Node=node::Node<Label>;
    
    if(argc!=2){
        std::cout<<"Wrong argument!"<<std::endl;
        return 0;
    }

    std::string filename(argv[1]);
    
    std::map<std::string, std::string> dataset_map;
    dataset_map=bowen::Dataset_path();
     std::map<std::string, std::string>::iterator it;
      it=dataset_map.find(filename);
    std::string trees_filepath;

    if(it==dataset_map.end()){
        std::cout<<"No such file!"<<std::endl;
        return 0;
    }
    else
        trees_filepath=it->second;

    
    analyzer:: Analyzer anly;

    std::vector<Node> trees_collection;
    anly.parse_collection(trees_collection,trees_filepath);
        
   // anly.parse_collection(trees_collection, file_path);
    anly.analyze_trees(trees_collection);
    
   //Node root=anly.parse_single(tree);
//
//    std::cout<<"root max depth: "<<root.getMax_depth()<<" root avg depth: "<<root.getAvg_depth()<<" root tree size: "<<root.getTree_size()<<std::endl;
    
    
   
   //std::cout<<"Valid: "<< anly.validate_input(tree)<<std::endl;
    return 0;
}
