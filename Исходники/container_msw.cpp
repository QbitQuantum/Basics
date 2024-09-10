//##############################################################################
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
//##############################################################################
void xContainerInternal::doLayout()
{
	//first our layout
	xDimension dim;
	getSize(dim);
	getLayout().getInternal()->setClientSize(dim,0,0);
	getLayout().getInternal()->doLayout();
	
	//then childs
	//automatically called for every child when resized
	
	/*
	smartPtr<xIterator> iter = m_components.iterator();
	while(iter->hasNext())
	{
		xContainer* c = dynamic_cast<xContainer*>(&(iter->next()));
		if(c != NULL)
			c->doLayout();
	}
	*/
}