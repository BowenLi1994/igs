
#ifndef delete_h
#define delete_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "../other/bfunction.h"



int delete(std::string filename, int deleted_line){


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





    return 0;
} 



#endif
