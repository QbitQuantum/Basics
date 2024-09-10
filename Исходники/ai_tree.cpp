void Tree::duplicateTree(Node *sourceNode, Node *destNode) {
    Common::Array<Node *> vUnvisited = sourceNode->getChildren();

    while (vUnvisited.size()) {
        Node *newNode = new Node(*(vUnvisited.end()));
        newNode->setParent(destNode);
        (destNode->getChildren()).push_back(newNode);
        duplicateTree(*(vUnvisited.end()), newNode);
        vUnvisited.pop_back();
    }
}