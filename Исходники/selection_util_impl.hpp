bool SelectRegion(Selector& sel, const typename TAAPos::ValueType& p, TAAPos& aaPos,
			   	  typename Grid::traits<typename TGeomObj::side>::callback cbRegionBoundary)
{
	typedef typename Grid::traits<TGeomObj>::iterator	TIter;

	if(!sel.grid())
		return false;

	Grid& g = *sel.grid();

//	first try to find the element which contains p
	TGeomObj* startElem = NULL;
	for(TIter iter = g.begin<TGeomObj>(); iter != g.end<TGeomObj>(); ++iter){
		if(ContainsPoint(*iter, p, aaPos)){
			startElem = *iter;
			break;
		}
	}

	if(!startElem)
		return false;

	sel.clear<TGeomObj>();
	sel.select(startElem);
	SelectionFill<TGeomObj>(sel, cbRegionBoundary);

	return true;
}