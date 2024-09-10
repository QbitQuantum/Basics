//指定のノードから親を辿り、第2指定のノードの直の子に打ち当たったら、そのノードを返す
Node* getChildOfTargetNodeUpstreamFrom(Node* from, Node* target) {
    Node* current = from;
    while (1) {
        if (current->getParent() == target) {
            return current;
        }
        else{
            current = current->getParent();
        }
    }
    return nullptr;
}