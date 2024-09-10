RelaxationPtr QPDRelaxer::createNodeRelaxation(NodePtr node, bool dived, 
                                               bool &prune)
{
  NodePtr t_node; 
  WarmStartPtr ws;

  prune = false;
  if (!dived) {
    // traceback to root and put in all modifications that need to go into the
    // relaxation and the engine.
    std::stack<NodePtr> predecessors;
    t_node = node->getParent();

    while (t_node) {
      predecessors.push(t_node);
      t_node = t_node->getParent();
    }

    // starting from the top, put in modifications made at each node to the
    // engine
    while (!predecessors.empty()) {
      t_node = predecessors.top();
      t_node->applyMods(qp_, p_);
      predecessors.pop();
    }
  } 

  // put in the modifications that were used to create this node from
  // its parent.
  node->applyMods(qp_, p_);

  // give the warm start info to the engine.
  ws = node->getWarmStart();
  if (ws) {
    qpe_->loadFromWarmStart(ws);
    node->removeWarmStart();
  }
  return qp_;
}