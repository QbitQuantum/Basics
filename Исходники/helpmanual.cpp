void HelpManual::buildContentTree(QTreeWidgetItem *parent, XMLNode TreeNode)
{
	XMLNode TempNode;
	QTreeWidgetItem *item;
	for (int i = 0; i < TreeNode.nChildNode("item"); ++i)
	{
		TempNode = TreeNode.getChildNode("item", i);
		item = new QTreeWidgetItem();
		item->setText(0, TempNode.getAttribute("name"));
		item->setText(1, TempNode.getAttribute("file"));
		item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
		parent->addChild(item);
		buildContentTree(item, TempNode);
	}
}