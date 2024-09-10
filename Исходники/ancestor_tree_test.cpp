TEST_F(AncestorTreeTest, add_node)
{
	unsigned long depth = 0;
	unsigned long mask = 1;
	unsigned char isNonzero = _BitScanReverse( &depth, mask);
	std::cout << depth << std::endl;

	directed::AncestorTree<int> tree;

	// depth 0
	directed::AncestorNode<int> * node_0 = tree.BuildNode(0);

	// depth 1
	directed::AncestorNode<int> * node_1 = tree.BuildNode(1);
	directed::AncestorNode<int> * node_2 = tree.BuildNode(2);

	// depth 2
	directed::AncestorNode<int> * node_3 = tree.BuildNode(3);
	directed::AncestorNode<int> * node_4 = tree.BuildNode(4);
	directed::AncestorNode<int> * node_5 = tree.BuildNode(5);
	directed::AncestorNode<int> * node_6 = tree.BuildNode(6);


	tree.SetRoot(node_0);

	node_0->SetLeft(node_1);
	node_0->SetRight(node_2);

	node_1->SetLeft(node_3);
	node_1->SetRight(node_4);
	node_2->SetLeft(node_5);
	node_2->SetRight(node_6);


	ASSERT_EQ(node_1, tree.LeastCommonAncestor(node_3, node_4));
	ASSERT_EQ(node_0, tree.LeastCommonAncestor(node_3, node_2));
	ASSERT_EQ(node_0, tree.LeastCommonAncestor(node_0, node_6));
	ASSERT_EQ(node_0, tree.LeastCommonAncestor(node_1, node_2));
	ASSERT_EQ(node_2, tree.LeastCommonAncestor(node_5, node_6));
	ASSERT_EQ(node_0, tree.LeastCommonAncestor(node_4, node_5));
	ASSERT_EQ(node_0, tree.LeastCommonAncestor(node_3, node_6));
}