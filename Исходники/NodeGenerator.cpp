void
Monitor::NodeGenerator::generate(TreeNode *t, QGraphicsScene *nodeScene, int w, int h, Node* parent)
{
  static int xpos = 0;
  static int ypos = 0;

  if (t == 0) {
    return;
  }

  Node *node = 0;

  QString text;
  if (isNodeValid(t, text)) {

    xpos = w * 100;
    ypos += 50;

    node = new Node(text, xpos, ypos, t);
    node->setParent(parent);

    // populate tooltips with the children
    TreeNode *c;
    std::ostringstream ttip;
    for (int i = 0; i < t->size(); ++i) {
      c = t->operator[](i);
      std::string k = c->column(0).toString().toLocal8Bit().constData();
      std::string v = c->column(1).toString().toLocal8Bit().constData();

      ttip << k << " : " << v << std::endl;
    }

    node->setToolTip(ttip.str().c_str());

    // this takes ownership of the node so the nodeScene will
    // cleanup all nodes when it's destroyed
    // TODO: This make each nodes parent the nodeScene. change this
    // so parent is the actual parent node using setParent()
    nodeScene->addItem(node);

    // connect us to our parent with a dashed line
    // connect us to the parent
    if (parent  && !nodeOpt_.hideParentChild()) {
      // give edge an actual parent so that z-order works
      Edge *edge = new Edge(parent, node, false,  parent);
      nodeScene->addItem(edge);
      parent->addEdge(edge);
      node->addEdge(edge);
    }
    // store node
    if (parent && !nodeOpt_.hidePubSub()) {
      nMap_[t] = node;
    }
  }

  // draw the child nodes
  ++w;
  for (int i = 0; i < t->size(); ++i) {
    generate(t->operator[](i), nodeScene, w, ++h, node);
  }

}