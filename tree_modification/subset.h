//
//  main.cpp
//  tree_subset
//
//  Created by Bowen Li on 6/21/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//


#ifndef subset_h
#define subset_h

#include <string>
#include <iostream>
#include <map>
#include "../other/bfunction.h"

int  subset(std::string filename, int trees_number) {
    
    //std::cout<<"Hello"<<std::endl;

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
    
    
    std::ifstream infile;
    std::ofstream outfile;
    
    //open file
    int trees_counter=0;
    
    infile.open(trees_filepath);
    if(!infile.is_open()){
        std::cout<<"cannot open the file: "<<filename<<std::endl;
        return 0;
    }
    
    
    std::string outfile_filepath="/home/bowen/igs_dataset/amazon/manual/";
    std::string outfile_filename=filename+std::to_string(trees_number)+".tree";
    std::cout<<outfile_filename<<std::endl;
    outfile.open(outfile_filepath+outfile_filename);
    if(!outfile.is_open()){
        std::cout<<"cannot open the file: "<<outfile_filename<<std::endl;
    }
    
    std::string trees_string;
    while (std::getline(infile,trees_string) && trees_counter<trees_number) {
        
        outfile<<trees_string;
        outfile<<"\n";
        trees_counter++;
        
    }
    
    infile.close();
    outfile.close();



    return 0;
    
}

#endif
