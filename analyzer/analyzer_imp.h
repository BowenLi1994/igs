//
//  analyzer_imp.h
//  analyzer
//
//  Created by Bowen Li on 4/7/20.
//  Copyright © 2020 Bowen Li. All rights reserved.
//

#ifndef analyzer_imp_h
#define analyzer_imp_h

/// This is currently a copy of the previous version but with the efficient
/// tokanization.
node::Node<Analyzer::Label> Analyzer::parse_single(
    const std::string& tree_string) {

  int id=1;
  int depth_couter=0;
    int total_depth=0;
    int max_depth=0;
  std::vector<std::string> tokens = get_tokens(tree_string);

  // Tokenize the input string - get iterator over tokens.
  auto tokens_begin = tokens.begin();
  auto tokens_end = tokens.end();

  // Deal with the root node separately.
  ++tokens_begin; // Advance tokens to label.
  std::string match_str = *tokens_begin;
  if (match_str == kLeftBracket || match_str == kRightBracket) { // Root has an empty label.
    match_str = "";
    // Do not advance tokens - we're already at kLeftBracket or kRightBracket.
  } else { // Non-empty label.
    ++tokens_begin; // Advance tokens.
  }
  Label root_label(match_str);
  node::Node<Label> root(root_label,id,depth_couter);
  node_stack.push_back(std::ref(root));
  id++;
  depth_couter++;
    total_depth+=depth_couter;
    if(depth_couter>max_depth)
        max_depth=depth_couter;
  // Iterate all remaining tokens.
  while (tokens_begin != tokens_end) {
    match_str = *tokens_begin;

    if (match_str == kLeftBracket) { // Enter node.
      ++tokens_begin; // Advance tokens to label.
      match_str = *tokens_begin;

      if (match_str == kLeftBracket || match_str == kRightBracket) { // Node has an empty label.
        match_str = "";
        // Do not advance tokens - we're already at kLeftBracket or kRightBracket.
      } else { // Non-empty label.
        ++tokens_begin; // Advance tokens.
      }

      // Create new node.
    total_depth+=depth_couter;
    if(depth_couter>max_depth)
        max_depth=depth_couter;
      Label node_label(match_str);
      node::Node<Label> n(node_label,id,depth_couter);
      id++;
      depth_couter++;
      //n.add_parent(node_stack.back().get()) ;
    
      node_stack.push_back(std::ref(node_stack.back().get().add_child(n)));
    }

    if (match_str == kRightBracket) { // Exit node.
      node_stack.pop_back();
      ++tokens_begin; // Advance tokens.
      depth_couter--;
    }
  }
    root.setTree_size(id-1);
    //total_depth-=depth_couter;
    int avg_depth=total_depth/(id-1);
    root.setAvg_depth(avg_depth);
    root.setMax_depth(max_depth);
  return root;
}
//
void Analyzer::parse_collection(
    std::vector<node::Node<Analyzer::Label>>& trees_collection,
    const std::string& file_path) {
  std::ifstream trees_file(file_path);
  if (!trees_file) {
    throw std::runtime_error("ERROR: Problem with opening the file '" + file_path + "' in BracketNotationParser::parse_collection_efficient.");
  }
  // Read the trees line by line, parse, and move into the container.
  std::string tree_string;
  while (std::getline(trees_file, tree_string)) {
    trees_collection.push_back(parse_single(tree_string)); // -> This invokes a move constructor (due to push_back(<rvalue>)).
  }
  trees_file.close();
}

/// This is only a tokanizer that returns a vector with correct tokens.
std::vector<std::string> Analyzer::get_tokens(
    const std::string& tree_string) {
  std::vector<std::string> tokens;

  // Get pointer to the structure elements.
  const char* s_elems = kStructureElements.c_str();

  // Get pointer to the beginning of the input string.
  const char* begin = tree_string.c_str();
  // Pointer to the beginning of consecutive searches.
  const char* next_begin = begin;
  // Remember iter from previous iteration in old_iter - for label begin.
  const char* old_iter = begin;
  // iter is a pointer to consecutive occurences of either '{' or '}'.
  for(const char* iter = strpbrk(next_begin, s_elems); iter != NULL; iter = strpbrk(next_begin, s_elems)) {
    // Next iteration will start from the position right of iter.
    next_begin = iter + 1;
    // Check if the character just before the found position is an escape_char.
    // Then, disregard the current position.
    if (iter > begin && *(iter-1) == kEscapeChar) {
      continue;
    }
    // If there is something between two consecutive brackets, it's potentially
    // a label - record it.
    if (iter > old_iter + 1) {
      tokens.push_back(typename std::vector<std::string>::value_type(old_iter+1, iter)); // Calls the allocator of string.
    }
    // Record the found bracket.
    tokens.push_back(typename std::vector<std::string>::value_type(iter, iter+1)); // Calls the allocator of string.
    old_iter = iter;
  }

  return tokens;
}

bool Analyzer::validate_input(const std::string& tree_string) const {
  int bracket_diff_counter = 0; // Counts difference between the numbers of left and right brackets.
  int bracket_pair_counter = 0; // Counts number of bracket pairs - number of nodes assuming correct nesting.
  // Loop over all characters.
  for(auto it = tree_string.begin(); it != tree_string.end(); ++it) {
    if (*it == kEscapeChar) { // Skip next character if kEscapeChar is found.
      ++it;
    } else if (*it == kLeftBracket[0]) { // Increase bracket_counter when kLeftBracket found.
      bracket_diff_counter++;
      bracket_pair_counter++;
    } else if (*it == kRightBracket[0]) { // Decrease bracket_counter when kRightBracket found.
      bracket_diff_counter--;
    }
  }
  if (bracket_diff_counter != 0 || bracket_pair_counter == 0) {
    return false;
  }
  return true;
}

void Analyzer::analyze_trees(const std::vector<Analyzer::Node>& trees_collection){
    
    std::cout<<"******Analyzing :******"<<std::endl;
    std::cout<<"Trees number: "<<trees_collection.size()<<std::endl;
    int total_avg_depth=0;
    int max_depth=0;
    int total_tree_size=0;
    int max_tree_size=0;
    
    for(const auto& root: trees_collection){
        
        total_tree_size+=root.getTree_size();
        if(root.getTree_size()>max_tree_size)
            max_tree_size=root.getTree_size();
        total_avg_depth+=root.getAvg_depth();
        if(root.getMax_depth()>max_depth)
            max_depth=root.getMax_depth();
        
    }
    
    double avg_tree_size=(double)total_tree_size/(double) trees_collection.size();
    
    double avg_depth=(double)total_avg_depth/(double) trees_collection.size();
    
    std::cout<<"Max size of tree: "<<max_tree_size<<std::endl;
    std::cout<<"Average size of tree: "<<avg_tree_size<<std::endl;
    std::cout<<"Max depth of tree: "<<max_depth<<std::endl;
    std::cout<<"Average depth of tree: "<<avg_depth<<std::endl;
    
}



#endif /* analyzer_imp_h */
