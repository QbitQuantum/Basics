void UpdateSwitch(SwitchNode *snode)
{
	int nNodes = snode->getNPrivateNodeElements();
	for (int n=0; n<nNodes; n++) {
		Node *node = snode->getPrivateNodeElementAt(n);
		node->remove();
	}
	Node *node = snode->getPrivateNodeElementAt(snode->getWhichChoice());
	if (node)
		snode->addChildNode(node);
}