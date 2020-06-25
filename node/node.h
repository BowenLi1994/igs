#ifndef NODE_NODE_H
#define NODE_NODE_H

#include <vector>
#include <string>

namespace node {
template <class Label>
class Node {
// Types and type aliases
public:
  using Reference = Label&;
  using ConstReference = const Label&;

  using SizeType = typename std::vector<Node<Label>>::size_type;

// Member functions
public:
  //Node();
  Node(ConstReference label,int id,int depth);
  const SizeType children_count() const;
  ConstReference label() const;
  Node<Label>& add_child(Node<Label> child);
  const std::vector<Node<Label>>& get_children() const;
  std::vector<Node<Label>>& get_nonconst_children();
  int get_tree_size() const;
  const std::vector<std::string> get_all_labels() const;
  void get_all_labels_recursion(std::vector<std::string>& labels) const;
  
  const std::vector<int> get_all_ids() const;
  void get_all_ids_recursion(std::vector<int>& ids) const;
    
  void print_all_label();
    
  bool is_leaf() const;
  int id() const;
    
  int depth() const;
  void setDepth(int depth);
    
    const int getTree_size() const;
    bool setTree_size(int size);
    
    const int getMax_depth() const;
    bool setMax_depth(int depth);
    
    const int getAvg_depth() const;
    bool setAvg_depth(int depth);
    
    const int getSibling_number() const;
    bool setSibling_number(int number);
    
    //const std::vector<Node<Label>>& get_parent() const;
    //Node<Label>& add_parent(Node<Label> node);
    
    //void set_sibling(const std::vector<Node<Label>>& sibling);
    
    //void print_parent();
    
// Member variables
private:
  /// All children of this node.
  std::vector<Node<Label>> children_;

  /// Data representing the label of this node. Only this Node object owns it.
  Label label_;
  //std::vector<Node<Label>> parent_;
  //std::vector<Node<Label>> sibling_;
  int id_;
  int depth_;
  int tree_size_;
  int max_depth_;
  int avg_depth_;
  int number_sibling_;
};

// Implementation details
#include "node_impl.h"

}

#endif // TREE_SIMILARITY_NODE_NODE_H
