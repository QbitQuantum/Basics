void udStateChartOptimizer::FindTransWithIdenticalTarget(ShapeList& transitions, ShapeList& sublist)
{
	sublist.Clear();

	ShapeList::compatibility_iterator node = transitions.GetFirst();
	if( !node ) return;

	wxSFLineShape *pTrans = (wxSFLineShape*)node->GetData();
	int nTrgId = pTrans->GetTrgShapeId();
	while(node)
	{
		pTrans = (wxSFLineShape*)node->GetData();
		if( pTrans->GetTrgShapeId() == nTrgId )
		{
			node = node->GetNext();
			transitions.DeleteObject(pTrans);
			sublist.Append(pTrans);
		}
		else
			node = node->GetNext();
	}
}