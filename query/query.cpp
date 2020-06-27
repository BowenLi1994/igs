//
//  main.cpp
//  query_generator
//
//  Created by Bowen Li on 6/25/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../igs/label/string_label.h"
#include "../../igs/node/node.h"
#include "../../igs/parser/bracket_notation_parser.h"
#include "../../igs/random/random_header.h"

int main(int argc, const char * argv[]) {
    
    using Label=label::StringLabel;
    using Node=node::Node<Label>;
    
    std::string filepath="/Users/brandonli/Desktop/igs/dataset/bolzano.tree";
    //std::string outfilepath="";
    parser::BracketNotationParser bnp;
    std::vector<Node> trees_collection;
    bnp.parse_collection(trees_collection, filepath);
    
    for(auto tree:trees_collection){
        
        int tree_size=tree.get_tree_size();
        uniform_d("random.txt", 1, 0, tree_size-1, 10);
        
        
        
        
    }
    
    
    
    return 0;
}
