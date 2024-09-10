void shape_mgr::get_rect(CRect &rect)
{
	rect.SetRect(0, 0, 0 ,0);
	if (shapes_.size() == 0)
		return;
	shapes_[0]->get_rect(rect);
	for (int i=1; i<shapes_.size(); i++)
	{
		CRect rc;
		shapes_[i]->get_rect(rc);
		rect.UnionRect(&rect, &rc);
	}
}