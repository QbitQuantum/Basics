void CMiscToolbar::ChildDialClosed(int dialnum,RDialog*,int rv)
{
	if (dialids[dialnum] && dialnum!=DIRECTIVESTOGGLE)
	{
		GETDLGITEM(dialids[dialnum])->SetPressed(FALSE);
		if (dialnum==0)
			CMIGView::m_thumbnail=NULL;
	}
}