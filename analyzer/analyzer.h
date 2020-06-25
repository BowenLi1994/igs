

#ifndef analyzer_h
#define analyzer_h

#include "../../igs/node/node.h"
#include "../../igs/label/string_label.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

namespace analyzer {

class Analyzer {
// Types and type aliases

public:
    using Label = label::StringLabel;
    using Node= node::Node<Label>;
    

// Member functions
public:
    
    node::Node<Label> parse_single(const std::string& tree_string);
    
    void parse_collection(std::vector<node::Node<Label>>& trees_collection,
      const std::string& file_path);
    
    std::vector<std::string> get_tokens(const std::string& tree_string);
    
    bool validate_input(const std::string& tree_string) const;
    
    void analyze_trees(const std::vector<Node>& trees_collection);
// Member variables

private:
    
    std::vector<std::reference_wrapper<Node>> node_stack;

  const std::string kLeftBracket = "{";
  const std::string kRightBracket = "}";
  const std::string kStructureElements = "{}";

  /// Escape character.
  const char kEscapeChar = '\\';

  /// A regex string to match left and right brackets.
  const std::string kMatchLeftBracket = "\\" + kLeftBracket;
  const std::string kMatchRightBracket = "\\" + kRightBracket;
};

// Implementation details
#include "analyzer_imp.h"

}
#endif /* analyzer_h */
