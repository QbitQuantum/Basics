void NodesHelper::remove(Contactable& contactable) {
    if (!active) return;
    Node *node = getNode(contactable.getName(),false);
    if (node) node->remove(contactable);
}