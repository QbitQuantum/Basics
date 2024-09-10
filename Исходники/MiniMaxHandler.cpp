void MiniMaxHandler::updateSpecificData(NodePtr pChild, NodePtr pLeaf, bool isPreUpdate)
{
	assert(pChild->isRoot() == false);
	if (isPreUpdate == false) {
		double dMaxWinRate = 0.0f;
		NodePtr pSibling = pChild->getLeftMost();
		for (; pSibling != nullptr; pSibling = pSibling->getRight()) {
			BfsData::Accessor siblingBfsData(pSibling);
			UctData::Accessor siblingUctData(pSibling);
			if (siblingBfsData.getWinningStatus() == BfsData::UNKNOWN && dMaxWinRate < siblingUctData.getWinRate())
				dMaxWinRate = siblingUctData.getWinRate();
		}
		double dParentNewWinRate = 1.0f - dMaxWinRate;
		UctData::Accessor parentUctData(pChild->getParent());
		parentUctData.setWinRate(dParentNewWinRate);
	}
	updateUcbScore(pChild->getParent());
}