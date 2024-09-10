//只改变大小,不改变位置
void CUIEditorView::sizingWindow(CPoint point,INT type,CEGUI::Window* pWin/* = NULL*/)
{
	CEGUI::Window* pWindow =  pWin ? pWin : m_pSelectedWindow;
	if (pWindow)
	{
		CEGUI::Window* pParent = pWindow;
		CEGUI::Size pt(0,0);
		if (pWindow->getParent() == CEGUI::System::getSingleton().getGUISheet())
		{
			CEGUI::Point pos = pWindow->getPixelRect().getPosition();
			pt = CEGUI::Size(point.x - pos.d_x, point.y - pos.d_y);
		}
		else
		{
			while (pParent && pParent->getParent() != CEGUI::System::getSingleton().getGUISheet())
			{
				pParent = pParent->getParent();
			}
			CEGUI::Rect	 rectWindow = pWindow->getPixelRect();
			pt = CEGUI::Size(point.x -rectWindow.getPosition().d_x   ,point.y -rectWindow.getPosition().d_y);
		}
		pWindow->setClippedByParent(true);
		if(type == 0)
		{
			pWindow->setHeight(CEGUI::Absolute,pt.d_height);
		}
		else if (type == 1)
		{
			pWindow->setWidth(CEGUI::Absolute,pt.d_width);
		}
		else
		{
			pWindow->setSize(CEGUI::Absolute, pt);
		}
	}
}