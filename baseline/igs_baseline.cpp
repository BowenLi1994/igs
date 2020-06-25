#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <string>
#include <unordered_map>

#include "../node/node.h"
#include "../label/string_label.h"
#include "../parser/bracket_notation_parser.h"
#include "../other/bfunction.h"
#include "baseline.h"
#include "../oracle/oracle_generator.h"


int main(int argc, const char * argv[]) {
    
    using Label=label::StringLabel;
    using Node=node::Node<Label>;
    
    parser::BracketNotationParser bnp;
    std::vector<Node> trees_collection;

    if(argc!=2){
      std::cout<<"Wrong arguments"<<std::endl;
      return 0;
    }
       
    
    std::map<std::string, std::string> dataset_map;
    dataset_map=bowen::Dataset_path();

    std::map<std::string, std::string>::iterator it;
    std::string filename(argv[1]);
    it=dataset_map.find(filename);
    std::string trees_filepath;


    if(it==dataset_map.end()){
        std::cout<<"No such file!"<<std::endl;
        return 0;
    }
    else
        trees_filepath=it->second;
	



    //std::string filename(argv[1]);
    //std::string trees_filepath="../dataset/"+filename+".tree";
    bnp.parse_collection(trees_collection, trees_filepath);

    
    std::string oracle_filepath="/home/bowen/igs_dataset/oracle/"+filename+".oracle";
    std::vector<int **> trees_oracle;
    oracle_generator::trees_collection_oracle_parser(trees_oracle,oracle_filepath);
    
    int trees_number=(int)trees_collection.size();
     std::map<int, std::pair<int, int>> total_depth_step;
    
       for(int i=0;i<trees_number;i++){
           int tree_size=trees_collection[i].get_tree_size();
           std::cout<<"**************"<<"tree: "<<i+1<<" size: "<<tree_size<<"**************"<<std::endl;
           int total_steps=0;
           std::map<int, std::pair<int, int>> tree_depth_step;
           for(int j=1;j<=tree_size;j++){
               Label target_label("target");
               Node target_node(target_label,j,0);
               bool found=0;
               int steps=1;
               baseline::Topdown(trees_collection[i],target_node,trees_oracle[i],found,steps);
               //std::cout<<"node: "<<j<<" steps: "<<steps<<std::endl;
               total_steps+=steps;
               //std::cout<<"depth: "<<target_node.depth()<<std::endl;
               std::map<int, std::pair<int, int>>::iterator it;
               it=tree_depth_step.find(target_node.depth());
               if(it!=tree_depth_step.end()){
                   it->second.first+=steps;
                   it->second.second++;
               }
               else
                   tree_depth_step.emplace(target_node.depth(),std::make_pair(steps, 1));
               
               it=total_depth_step.find(target_node.depth());
               if(it!=total_depth_step.end()){
                   it->second.first+=steps;
                   it->second.second++;
               }
               else
                   total_depth_step.emplace(target_node.depth(),std::make_pair(steps, 1));
                
           }
           std::cout<<"average step for each tree:"<<total_steps/tree_size<<std::endl;
          
           for(auto map:tree_depth_step){
               int average=map.second.first/map.second.second;
               std::cout<<"depth: "<<map.first<<" number of nodes: "<<map.second.second<<" average steps: "<<average<<std::endl;
           }
       }
        std::cout<<"Final analysis"<<std::endl;
        for(auto map:total_depth_step){
                  int average=map.second.first/map.second.second;
                  std::cout<<"depth: "<<map.first<<" number of nodes: "<<map.second.second<<" average steps: "<<average<<std::endl;
              }





    
    
    
    
        return 0;
}

