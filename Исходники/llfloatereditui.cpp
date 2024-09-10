void	LLFloaterEditUI::navigateHierarchyButtonPressed(void*	data)
{
	LLView* view = LLView::sEditingUIView;
	if( !view ) return;
	LLView*	parent = view->getParent();
	if(!parent)
	{
		return ;
	}
	const LLView::child_list_t*	viewChildren = view->getChildList();
	const LLView::child_list_t*	parentChildren = parent->getChildList();
	//LLView::child_list_t::iterator
	std::list<LLView*>::const_iterator	itor;
	std::list<LLView*>::size_type	idx;
	std::list<LLView*>::size_type	sidx;
	for(idx = 0,itor = parentChildren->begin();itor!=parentChildren->end();itor++,idx++){
		if((*itor)==view)break;
	}
	switch((intptr_t)data)
	{
		case	0	://up
			view = view->getParent();
		break;
		case	1	://down
			view = viewChildren->begin()!=viewChildren->end() ? (*viewChildren->begin()) : NULL;
		break;
		case	2	://left
		{			
			if(idx==0)
				idx = parentChildren->size()-1;
			else
				idx--;
			if( (long) idx < 0 || idx >= parentChildren->size())break;
			for(sidx = 0,itor = parentChildren->begin();itor!=parentChildren->end();itor++,sidx++){
				if(sidx == idx)
				{
					view = (*itor);
					break;
				}
			}
		}
		break;
		case	3	://right
		{
			if(idx==parentChildren->size()-1)
				idx = 0;
			else
				idx++;
			if( (long) idx < 0 || idx >= parentChildren->size())break;
			for(sidx = 0,itor = parentChildren->begin();itor!=parentChildren->end();itor++,sidx++){
				if(sidx == idx)
				{
					view = (*itor);
					break;
				}
			}
		}
		break;
	}
	if (view)
	{
		sEditingUIView = view;
		sInstance->refresh();
	}
}