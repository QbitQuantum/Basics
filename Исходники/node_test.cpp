TEST_F(NodeTest, testGetMindMap)
{
    Node* nodeParent = new Node(2);
    Root* root = new Root(1);
    _node->setParent(nodeParent);
    nodeParent->setParent(root);
    ASSERT_EQ(root, _node->getMindMap());
    ASSERT_EQ(root, nodeParent->getMindMap());
}