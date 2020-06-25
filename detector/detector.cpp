#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../node/node.h"
#include "../label/string_label.h"
#include "../parser/bracket_notation_parser.h"
#include "../other/bfunction.h"

int main(void){

    using Lable=label::StringLabel;
    using Node=node::Node<Lable>;

    std::string filepath="/home/bowen/igs_dataset/amazon/manual/All10000.tree";

    std::vector<std::string> lines;

    bowen::ReadFile(filepath,lines);

    //std::cout<<lines[705]<<std::endl;
    
    parser::BracketNotationParser bnp;
    
    //bnp.parse_single(lines[705]).print_all_label();

    //std::cout<< bnp.validate_input(lines[705])<<std::endl;
    
    std::vector<std::string>tokens= bnp.get_tokens(lines[705]);
    for(auto t:tokens){
        std::cout<<t<<std::endl;
    }
   



}
