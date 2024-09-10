void MindMapModel::editNodeParent(int nodeID, int parentID)
{
	Component *node = findTargetNode(nodeID, root);
	Component *newParent = findTargetNode(parentID, root);

	cmd = new ChangeParentCommand(node, node->getParent(), newParent);

	cmdManager.execute(cmd);
}