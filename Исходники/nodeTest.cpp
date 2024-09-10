TEST_F(nodeTest, testAddSibling)
{
	Component *parent = new Node("Computer", 2);
	Component *temp = new Node("OS", 3);
	node->addParent(parent);
	node->addSibling(temp);
	EXPECT_EQ(node->getParent()->getID(), temp->getParent()->getID());
	EXPECT_EQ(node->getParent()->getDescription(), temp->getParent()->getDescription());
}