//查找路径
//isEnding：为真表示curNode是路径的结束点（4个方向不通，不能往回走）
bool NDFindPath::getPath(unsigned int uiTileX, unsigned int uiTileY,
						 NDPathNode* curNode, bool isEnding)
{
	if (!m_mapGraph)
		return false;

	if (0 != curNode)
	{
		//路径判定：点数匹配
		if (m_uiRollNumber == curNode->stepNumber)
		{
			TilePath kPaths;
			NDPathNode* tmpNode = curNode;
			while (0 != tmpNode)
			{
				kPaths.push(tmpNode);
				tmpNode = tmpNode->preNode;
			}

			m_vecPath.push_back(kPaths);
			return true;
		}

		//路径判定：经过出口
		if (curNode->bExit && 0 != curNode->stepNumber)
		{
			TilePath kPaths;
			NDPathNode* tmpNode = curNode;

			while (0 != tmpNode)
			{
				kPaths.push(tmpNode);
				tmpNode = tmpNode->preNode;
			}

			m_vecPath.push_back(kPaths);

			//这里不return，接着寻路...
		}
	}

	//获取当前坐标的GraphNode
	const GRAPH_NODE* pkGraphNode = m_mapGraph->getGraphNode_Const(uiTileX,
		uiTileY);
	if (!pkGraphNode)
		return false;

	//新建一个路径节点
	NDPathNode* pathNode = new NDPathNode;
	{
		int stepNumber = (curNode ? curNode->stepNumber + 1 : 0); //起点为0!
		pathNode->init(uiTileX, uiTileY, pkGraphNode->isExit, stepNumber,
			curNode);
	}

	//尝试4个方向的寻路
	if (!isEnding)
	{
		bool bhasWay = false;

		//左
		if (pkGraphNode->left)
		{
			if (0 == curNode)
			{
				getPath(uiTileX - 1, uiTileY, pathNode);
				bhasWay = true;
			}
			else if (curNode->x != uiTileX - 1 || curNode->y != uiTileY) //不允许回退！
			{
				getPath(uiTileX - 1, uiTileY, pathNode);
				bhasWay = true;
			}
		}

		//上
		if (pkGraphNode->up)
		{
			if (0 == curNode)
			{
				getPath(uiTileX, uiTileY - 1, pathNode);
				bhasWay = true;
			}
			else if (curNode->x != uiTileX || curNode->y != uiTileY - 1)
			{
				getPath(uiTileX, uiTileY - 1, pathNode);
				bhasWay = true;
			}
		}

		//右
		if (pkGraphNode->right)
		{
			if (0 == curNode)
			{
				getPath(uiTileX + 1, uiTileY, pathNode);
				bhasWay = true;
			}
			else if (curNode->x != uiTileX + 1 || curNode->y != uiTileY)
			{
				getPath(uiTileX + 1, uiTileY, pathNode);
				bhasWay = true;
			}
		}

		//下
		if (pkGraphNode->down)
		{
			if (0 == curNode)
			{
				getPath(uiTileX, uiTileY + 1, pathNode);
				bhasWay = true;
			}
			else if (curNode->x != uiTileX || curNode->y != uiTileY + 1)
			{
				getPath(uiTileX, uiTileY + 1, pathNode);
				bhasWay = true;
			}
		}

		//4个方向都不通（不允许回退）
		if (!bhasWay)
		{
			if (curNode && curNode == pathNode)
			{

			}
			else
			{
				getPath(uiTileX, uiTileY, pathNode, true);
			}
		}
	}

	return true;
}