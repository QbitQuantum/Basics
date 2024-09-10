void CWndManager::PaintRoot()
{
	const QPoint oldOrigin = m_render2D->Origin();
	const QRect oldViewport = m_render2D->Viewport();
	CWndControl* ctrl = null;
	QRect rect, viewport;
	int remove;

	for (int i = 0; i < m_controls.GetSize(); i++)
	{
		ctrl = m_controls[i];

		remove = m_removeControls.Find(ctrl);
		if (remove != -1)
		{
			Delete(ctrl);
			m_removeControls.RemoveAt(remove);
			m_controls.RemoveAt(i);
			i--;
			continue;
		}

		rect = ctrl->GetWindowRect(true);
		if (oldViewport.intersects(rect))
		{
			viewport = rect;
			if (viewport.left() < oldViewport.left()) viewport.setLeft(oldViewport.left());
			if (viewport.top() < oldViewport.top()) viewport.setTop(oldViewport.top());
			if (viewport.right() > oldViewport.right()) viewport.setRight(oldViewport.right());
			if (viewport.bottom() > oldViewport.bottom()) viewport.setBottom(oldViewport.bottom());
			m_render2D->SetOrigin(rect.topLeft());
			m_render2D->SetViewport(viewport);
			ctrl->Paint(rect, oldViewport);
		}
	}

	if (s_selection.GetSize() > 0)
	{
		for (int i = 0; i < m_controls.GetSize(); i++)
		{
			ctrl = m_controls[i];
			rect = ctrl->GetWindowRect(true);
			ctrl->RenderSelection(rect, oldViewport);
		}
	}

	m_render2D->SetOrigin(oldOrigin);
	m_render2D->SetViewport(oldViewport);
}