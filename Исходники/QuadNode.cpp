RectangleT QuadNode::calculateRect( QuadNode* n )
{
	if (n == NULL)
	{
		return RectangleT::Zero;
	}
	if (n->leaf_)
	{
		Chunk* ck = getSceneManager()->getTerrain()->getChunkFromTopology(n->xNumber_, n->zNumber_);
		n->rect_ = ck->getRect();
		return n->rect_;
	}
	return unionRect(n);
}