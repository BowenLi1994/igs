
#ifndef TREE_SIMILARITY_NODE_NODE_IMPL_H
#define TREE_SIMILARITY_NODE_NODE_IMPL_H

//template<class Label>
//Node<Label>::Node():label_("NULL"),id_(0),depth_(0){}

template<class Label>
Node<Label>::Node(ConstReference label,int id,int depth) : label_(label),id_(id),depth_(depth) {}




template<class Label>
const typename Node<Label>::SizeType Node<Label>::children_count() const {
  return children_.size();
}

template<class Label>
typename Node<Label>::ConstReference Node<Label>::label() const {
  return label_;
}

template<class Label>
Node<Label>& Node<Label>::add_child(Node<Label> child) {
  children_.push_back(child);
  return children_.back();
}

template<class Label>
const std::vector<Node<Label>>& Node<Label>::get_children() const {
  return children_;
}

template<class Label>
int Node<Label>::get_tree_size() const {
  int size = 1;
  for (const auto& child : children_) {
    size += child.get_tree_size();
  }
  return size;
}

template<class Label>
const std::vector<std::string> Node<Label>::get_all_labels() const {
  std::vector<std::string> labels;
  get_all_labels_recursion(labels);
  return labels;
}
template<class Label>
void Node<Label>::get_all_labels_recursion(std::vector<std::string>& labels) const {
  labels.push_back(label_.to_string());
  for (const auto& child : children_) {
    child.get_all_labels_recursion(labels);
  }
}


template<class Label>
const std::vector<int> Node<Label>::get_all_ids() const {
  std::vector<int> ids;
  get_all_ids_recursion(ids);
  return ids;
}

template<class Label>
void Node<Label>::get_all_ids_recursion(std::vector<int>& ids) const {
  ids.push_back(id_);
  for (const auto& child : children_) {
    child.get_all_ids_recursion(ids);
  }
}

template<class Label>
void Node<Label>::print_all_label(){
   std::cout<<"label id: "<<this->id()<<" <-";
   //this->print_parent();
   for(auto child: children_){
       std::cout<<"node: "<<label_.to_string()<<" id: "<<id_<<" depth: "<<depth_<<"-->"<<child.label().to_string()<<" id: "<<child.id()<<" depth: "<<child.depth()<<std::endl;
      
       child.print_all_label();
   }
    
}


template<class Label>
bool Node<Label>::is_leaf() const {
  return children_.size() == 0;
}

template<class Label>
int Node<Label>::id() const{
    
    return id_;
}

template<class Label>
int Node<Label>::depth() const{
    
    return depth_;
}

template<class Label>
void Node<Label>::setDepth(int depth){
    depth_=depth;
}


template<class Label>
std::vector<Node<Label>>& Node<Label>::get_nonconst_children(){
    
    return children_;
}

template<class Label>
const int Node<Label>::getTree_size() const{
    return tree_size_;
}

template<class Label>
bool Node<Label>::setTree_size(int t){
    tree_size_=t;
    
    return true;
}

template<class Label>
const int Node<Label>::getMax_depth() const{
    return max_depth_;
}

template<class Label>
bool Node<Label>::setMax_depth(int depth){
    
    max_depth_=depth;
    
    return true;
}

template<class Label>
const int Node<Label>::getAvg_depth() const{
    return avg_depth_;
}

template<class Label>
bool Node<Label>::setAvg_depth(int depth){
   
    avg_depth_=depth;
    
    return true;
}

//template<class Label>
// const std::vector<Node<Label>>&  Node<Label>::get_parent() const{
//
//   return parent_;
//}
//
//template<class Label>
//Node<Label>& Node<Label>::add_parent(Node<Label> node){
//
//    //parent_.push_back(node);
//    return parent_.back();
//}
//
//template<class Label>
//void Node<Label>::print_parent(){
//    if(parent_.size()==0){
//        std::cout<<"No parent"<<std::endl;
//    }
//    else
//        std::cout<<"parent id: "<<parent_.begin()->id()<<std::endl;
//}
//
//template<class Label>
//void Node<Label>::set_sibling( const std::vector<Node<Label>>& sibling){
//    sibling_=sibling;
//}

template<class Label>
const int Node<Label>::getSibling_number() const{
    return number_sibling_;
}

template<class Label>
bool Node<Label>::setSibling_number(int number){
    number_sibling_=number;
    
    return true;
}


#endif // TREE_SIMILARITY_NODE_NODE_IMPL_H
