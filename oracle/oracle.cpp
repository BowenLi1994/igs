#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <string>
#include <map>
#include <fstream>

#include "../node/node.h"
#include "../label/string_label.h"
#include "../parser/bracket_notation_parser.h"
#include "oracle_generator.h"



int main(int argc, const char * argv[]) {

       using Label=label::StringLabel;
       using Node=node::Node<Label>;
       
      
    if(argc!=2){
        std::cout<<"Wrong arguments!"<<std::endl;
        return 0;
        }   
    
       std::map<std::string, std::string> dataset_map;
       dataset_map=bowen::Dataset_path();

       std::map<std::string, std::string>::iterator it;
       std::string filename(argv[1]);
       it=dataset_map.find(filename);
        std::string trees_filepath;

        //for(auto map: dataset_map){
           // std::cout<<"file: "<<map.first<<" path: "<<map.second<<std::endl;
        //}

        if(it==dataset_map.end()){
          std::cout<<"No such file!"<<std::endl;
          return 0;
        }
        else
          trees_filepath=it->second;


    //std::cout<<"argc: "<<argc<<std::endl;

 
       
       parser::BracketNotationParser bnp;
       std::vector<Node> trees_collection;

       //std::string filename="singel_case3";
      
       //std::string trees_filepath="../dataset/singel_case3.tree";

       bnp.parse_collection(trees_collection, trees_filepath);

       oracle_generator::trees_collection_oracle_generator(trees_collection, filename);
    


    //std::string filepath="./test.txt";
    //std::vector<int **> trees_oracle;
    //oracle_generator::trees_collection_oracle_parser(trees_oracle, filepath);
    //std::cout<<trees_oracle.size()<<std::endl;

  return 0;
    
}
