int Combining_Tree::getAndIncrement(int thread_id){
  std::list <Node*> nodes_stack;
  Node * myLeaf      = this->leaf_[thread_id / 2];
  Node * node        = myLeaf;
  
  // determine first or second node reach to a point
  while(node->pre_combine()){
    node             = node->getParent();    // climb to the parent node
  }
  Node * stop        = node;            // set the highest point the climb reached
  node               = myLeaf;          // set node to original point
  
  int combined       = 1;               // make an increase on here.
  
  while (node != stop){                 // do combining until reach the stop point.
    combined         = node->combine(combined);  // combine each point along with climbing.
    nodes_stack.push_back(node);                 // trace the node reached.
    node             = node->getParent();        // climb up 
  }

  int prior = stop->op(combined);        // set the final increased value to the stop point

  while(!nodes_stack.empty()) {          // iterater all the element in the stack
    node             = nodes_stack.back();  
    nodes_stack.pop_back();              
    node->distribute(prior);             // call distribute function to all waiting thread
  }

  return prior;
}