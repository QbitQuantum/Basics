void TBScroller::GetTargetScrollXY(int &x, int &y) const
{
	x = 0;
	y = 0;
	TBWidget *tmp = m_target->GetScrollRoot();
	while (tmp)
	{
		TBWidget::ScrollInfo info = tmp->GetScrollInfo();
		x += info.x;
		y += info.y;
		tmp = tmp->GetParent();
	}
}