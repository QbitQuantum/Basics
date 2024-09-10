	void SnakeLayer::truncate()
	{
		float lengthSoFar = 0;
		auto itr = lineGroup->getChildren().rbegin();
		LineNode* n = nullptr;
		for (; itr != lineGroup->getChildren().rend(); itr++)
		{
			n = static_cast<LineNode*>(*itr);
			float thisLength = (n->getEnd() - n->getStart()).getLength();
			if (lengthSoFar + thisLength > maximumLength) break;
			lengthSoFar += thisLength;
		}

		if (itr == lineGroup->getChildren().rend() || !n) return;
		Point vn = n->getStart() - n->getEnd();
		vn.normalize();
		float tailLength = maximumLength - lengthSoFar;
		n->setStart(n->getEnd() + vn * tailLength);

		itr++;
		vector<Node*> nodesToDelete;
		for (; itr != lineGroup->getChildren().rend(); itr++)
			nodesToDelete.push_back(*itr);

		for (auto node : nodesToDelete) lineGroup->removeChild(node);
	}