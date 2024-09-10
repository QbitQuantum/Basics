bool BrowserWindow::_OnMouseEvent(MouseEvent* e,const math::rectf& ownerRect)
{
	if(!ownerRect.IsPointInside(e->pos))
		return false;
	if(e->event==MET_MOVED)
	{

		math::vector2d mapped=e->pos-ownerRect.ULPoint;
		mapped=m_impl->mapCoord(mapped,ownerRect.getSize());
		//mapped=mapped*m_impl->window->GetSize()/GetDefaultRegion()->GetRect().getSize();
		m_impl->GetWindow()->mouseMoved(mapped.x,mapped.y);
		m_impl->GetWindow()->mouseWheel(0,e->MouseWheelRel);
	}
	if(e->event==MET_LEFTDOWN)
	{
		m_impl->GetWindow()->mouseButton(0,true);
	}else
		if(e->event==MET_LEFTUP)
			m_impl->GetWindow()->mouseButton(0,false);
		else
			if(e->event==MET_MIDDLEDOWN)
				m_impl->GetWindow()->mouseButton(1,true);
			else
				if(e->event==MET_MIDDLEUP)
					m_impl->GetWindow()->mouseButton(1,false);
				else
					if(e->event==MET_RIGHTDOWN)
						m_impl->GetWindow()->mouseButton(2,true);
					else
						if(e->event==MET_RIGHTUP)
							m_impl->GetWindow()->mouseButton(2,false);
	return true;
}