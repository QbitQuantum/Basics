void CRender::SelectItemsWithin(const RectF &r)
{
	CComPtr<boost::scoped_lock_ref_counted> lock;
	CComPtr<IGraphItem> item;
	CComPtr<IUnknown> unk;
	CComQIPtr<IRenderer> ir;
	RectF box;

	IGraphItemVector results;
	m_graph->GetChildren(results);

	for(IGraphItemVector::iterator itr=results.begin(); itr!=results.end(); ++itr)
	{
		item=*itr;			
		unk=item->GetPropertyUnknown(0);

		if(unk)
		{
			ir=static_cast<IRenderer*>(unk.p);
			if(ir!=0)
			{
				ir->GetBoundsBox(box);
				if(box.IntersectsWith(r))
					ir->SetSelected(true, true);
			}
		}
	}
}