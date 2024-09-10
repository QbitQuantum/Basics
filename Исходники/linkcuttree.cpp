Node* LinkCutTree::_cleanUp(Node* vertex) {
    Node* root;
    
    if(vertex->parent) {
        root = _cleanUp(vertex->parent);
    } else {
        root = vertex;
    }
    
    Node::push(vertex);
    
    return root;
}