void 
IntervalRTreeBranchNode::query( double queryMin, double queryMax, index::ItemVisitor * visitor) const
{
	if (! intersects(queryMin, queryMax)) 
		return;

	if (node1) 
		node1->query( queryMin, queryMax, visitor);

	if (node2) 
		node2->query( queryMin, queryMax, visitor);
}