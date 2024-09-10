TEST_F(NodeTest, NodeInitiallyHasNoParent)
{
	Node testObject;
	EXPECT_EQ((INode*)0, testObject.GetParent());
}