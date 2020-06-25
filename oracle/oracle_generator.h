//
//  oracle_generator.h
//  igs_baseline_tree
//
//  Created by Bowen Li on 2/25/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef oracle_generator_h
#define oracle_generator_h

#include "../label/string_label.h"
#include "../node/node.h"
#include "../other/bfunction.h"
#include <vector>
#include <utility>
#include <fstream>
#include <cmath>
namespace oracle_generator{


using Label=label::StringLabel;
using Node=node::Node<Label>;

void trees_collection_oracle_generator( std::vector<Node>& trees_collection,std::string filepath);
void singel_tree_generator(const Node& root,int** matrix);
void get_oracle_recursion(int ** matrix,const Node & root);

void single_tree_oracle_parser(const std::string& line,int** oracle_matrix,int tree_size);
void trees_collection_oracle_parser(std::vector<int **> &trees_oracle,std::string filepath);



void singel_tree_generator(const Node& root, int** matrix){

    //std::vector<oracle> tree_oracle;
    get_oracle_recursion(matrix, root);
    
    
}

void get_oracle_recursion(int** matrix, const Node & root){

    std::vector<int> ids=root.get_all_ids();
    //ids.erase(ids.begin());
    for(const auto id:ids)
        matrix[root.id()-1][id-1]=1;
    for(const auto& child:root.get_children())
        get_oracle_recursion(matrix, child);



}


void trees_collection_oracle_generator( std::vector<Node>& trees_collection,std::string filename){

    std::ofstream myfile ("/home/bowen/igs_dataset/oracle/"+filename+".oracle");
    for(auto root:trees_collection){
        int ** oracle_matrix;
        int tree_size=root.get_tree_size();
        //std::cout<<tree_size<<std::endl;
        oracle_matrix = new int*[tree_size];
        for(int i = 0; i < tree_size; ++i)
            oracle_matrix[i] = new int[tree_size];
        for(int i=0;i<tree_size;i++)
            for(int j=0;j<tree_size;j++)
                oracle_matrix[i][j]=0;
        singel_tree_generator(root, oracle_matrix);
     
        if (myfile.is_open())
        {
            
          for(int i=0;i<tree_size;i++){
              for(int j=0;j<tree_size;j++){
                  myfile<<std::to_string(oracle_matrix[i][j]);
                  }
                }
            myfile<<std::endl;
            
        }
    }
        myfile.close();
    
        
}
        


void single_tree_oracle_parser(const std::string& line,int** oracle_matrix,int tree_size){
    
    //std::cout<<line<<std::endl;
    for(int i=0;i<tree_size;i++){
        for(int j=0;j<tree_size;j++){
            int value=line[i*tree_size+j]-'0';
            oracle_matrix[i][j]=value;
            }
        }
}



void trees_collection_oracle_parser(std::vector<int **> &trees_oracle,std::string filepath){
       
        std::vector<std::string> lines;
        bowen::ReadFile(filepath, lines);
        for(auto line: lines){
            
            int tree_size=(int)sqrt(line.length());
            int** oracle_matrix;
            oracle_matrix = new int*[tree_size];
            for(int i = 0; i < tree_size; ++i)
                oracle_matrix[i] = new int[tree_size];
            for(int i=0;i<tree_size;i++)
                for(int j=0;j<tree_size;j++)
                    oracle_matrix[i][j]=0;
            oracle_generator::single_tree_oracle_parser(line, oracle_matrix,tree_size);
            
            trees_oracle.push_back(oracle_matrix);
            
        }
}






}







#endif /* oracle_generator_h */
