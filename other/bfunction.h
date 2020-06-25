#ifndef BFUNCTION_H
#define BFUNCTION_H

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>
namespace bowen{


std::map<std::string,std::string> Dataset_path();
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
void ReadFile(const std::string filepath, std::vector<std::string> &lines);


void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
        
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}



void ReadFile(const std::string filepath, std::vector<std::string> &lines){
    
    std::ifstream infile(filepath);

    std::string line;
    if(infile.is_open()){
        while (std::getline(infile, line)){
            lines.push_back(line);
        }         
    }
    else
        std::cout<<filepath<<" cannot be open"<<std::endl; 

}

std::map<std::string,std::string> Dataset_path(){
    std::map<std::string,std::string> dataset_map;
    std::string filepath="/home/bowen/igs/other/dataset.map";
    std::vector<std::string> lines;
    ReadFile(filepath,lines);
    for(auto line:lines){
        //std::cout<<line<<std::endl;
        std::vector<std::string> tokens;
        SplitString(line,tokens,"-");
        //std::cout<<"token1: "<<tokens[0]<<" token2: "<<tokens[1]<<std::endl;
        dataset_map.emplace(tokens[0],tokens[1]);
    }

    return dataset_map;

}


}



#endif
