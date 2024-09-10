void DisplayNodeVisitor::visitor(Root* root)
{
	stringstream ss;
	int depth = 1;
	string blank(depth * 2, ' ');  //計算深度的空白數量
	int indexDepth = 0;
	ss << "＋－" << root->getDescription() << "(" << root->getType() << "," << "ID:" << root->getId() << ")" << endl;  //印出節點內容
	list<Component*> nodeList(root->getNodeList());
	for (list<Component *>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		for (indexDepth = 0; indexDepth < depth; indexDepth++)	//print 前置空白
		{
			Component* parent = (*it);
			for (int i = 0; i < depth - indexDepth; i++)
			{
				parent = parent->getParent();
			}
			if (indexDepth >= 1 && parent->haveSibling()) // not root && have sibling
				ss << "｜　";
			else
				ss << "　　";  //two sapce
		}
		ss << (**it).getMap(depth + 1).str();
	}
	cout << ss.str();
}