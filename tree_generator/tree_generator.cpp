#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../node/node.h"
#include "../label/string_label.h"
#include "../other/bfunction.h"
#include "../parser/bracket_notation_parser.h"


//tree_number size depth
int main(int argc, const char * argv[]) {
    
    using Label=label::StringLabel;
    using Node=node::Node<Label>;
 
    std::vector<std::string> result;

    //std::string filename(argv[1]);
    std::map<std::string, std::string> dataset_map;
    dataset_map=bowen::Dataset_path();
    std::map<std::string, std::string>::iterator it;
    std::string filename(argv[1]);
    it=dataset_map.find(filename);
    std::string trees_filepath;

    if(it==dataset_map.end()){
        std::cout<<"No such file!"<<std::endl;        
        return 0;
    }else
        trees_filepath=it->second;
    
    std::ifstream infile(trees_filepath);

    if(infile.is_open()==0){

      std::cout<<"cannot open file"<<std::endl;
      return 0;
    }

    std::string line;
    int counter=0;
    std::string trees_no(argv[2]);
    std::string type(argv[3]);
    std::string threshold(argv[4]);

    int trees_number=std::stoi(trees_no);
    int size_threshold=std::stoi(threshold);

    while (std::getline(infile, line)){

      //std::cout<<"line: "<<line<<std::endl;
      parser::BracketNotationParser bnp;

      Node root=bnp.parse_single(line);

      int tree_size=root.get_tree_size();
      int depth=root.getMax_depth();

      if(type=="depth"){
          if(depth>=size_threshold){
              result.push_back(line);
              counter++;
          }
      }

      //if(tree_size>=1000){
    //result.push_back(line);
        //counter++;
      //}
      //
      if(type=="size"){
          if(tree_size>=size_threshold){
              result.push_back(line);
              counter++;
          }
      }

      if(counter==trees_number)
          break;


      

      //std::cout<<"tree size: "<<tree_size<<" depth: "<<depth<<std::endl;    

    } 

    std::string write_name=filename+trees_no+type+threshold;
    std::ofstream myfile ("/home/bowen/igs_dataset/amazon/manual/"+write_name+".tree");  
    if (myfile.is_open()){
      for(auto tree_string : result){
        myfile<<tree_string+"\n";
      }
    }
    myfile.close();



    return 0;
}
