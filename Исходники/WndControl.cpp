void CWndControl::Paint(const QRect& windowRect, const QRect& parentRect)
{
    if (!HasFlag(WBS_NODRAWFRAME))
        PaintFrame();

    const QRect viewport = m_render2D->Viewport();
    const QRect clientRect(GetClientRect(false).topLeft() + windowRect.topLeft(), m_clientRect.size());
    QRect viewRect, childViewRect;

    viewRect = clientRect;
    if (viewRect.left() < viewport.left()) viewRect.setLeft(viewport.left());
    if (viewRect.top() < viewport.top()) viewRect.setTop(viewport.top());
    if (viewRect.right() > viewport.right()) viewRect.setRight(viewport.right());
    if (viewRect.bottom() > viewport.bottom()) viewRect.setBottom(viewport.bottom());

    if (!HasFlag(WBS_CHILD))
    {
        m_render2D->SetViewport(viewRect);
        m_render2D->SetOrigin(clientRect.topLeft());
        EraseBackground();
    }

    if (m_controls.GetSize() > 0)
    {
        QRect rect;
        CWndControl* child;
        for (int i = 0; i < m_controls.GetSize(); i++)
        {
            child = m_controls[i];
            if (child->HasFlag(WBS_CHILD))
            {
                rect = child->GetWindowRect(true);
                if (child->HasFlag(WBS_DOCKING))
                {
                    rect = QRect(windowRect.topLeft() + rect.topLeft(), rect.size());
                    if (viewport.intersects(rect))
                    {
                        childViewRect = rect;
                        if (childViewRect.left() < viewport.left()) childViewRect.setLeft(viewport.left());
                        if (childViewRect.top() < viewport.top()) childViewRect.setTop(viewport.top());
                        if (childViewRect.right() > viewport.right()) childViewRect.setRight(viewport.right());
                        if (childViewRect.bottom() > viewport.bottom()) childViewRect.setBottom(viewport.bottom());
                        m_render2D->SetOrigin(rect.topLeft());
                        m_render2D->SetViewport(childViewRect);
                        child->Paint(rect, viewport);
                    }
                }
                else
                {
                    rect = QRect(clientRect.topLeft() + rect.topLeft(), rect.size());
                    if (viewport.intersects(rect))
                    {
                        childViewRect = rect;
                        if (childViewRect.left() < viewport.left()) childViewRect.setLeft(viewport.left());
                        if (childViewRect.top() < viewport.top()) childViewRect.setTop(viewport.top());
                        if (childViewRect.right() > viewport.right()) childViewRect.setRight(viewport.right());
                        if (childViewRect.bottom() > viewport.bottom()) childViewRect.setBottom(viewport.bottom());
                        m_render2D->SetOrigin(rect.topLeft());
                        m_render2D->SetViewport(childViewRect);
                        child->Paint(rect, viewport);
                    }
                }
            }
        }
    }

    m_render2D->SetOrigin(clientRect.topLeft());
    m_render2D->SetViewport(viewRect);
    Draw();

    if (s_selection.GetSize() > 0 && m_controls.GetSize() > 0)
    {
        QRect rect;
        CWndControl* child;
        for (int i = 0; i < m_controls.GetSize(); i++)
        {
            child = m_controls[i];
            if (child->HasFlag(WBS_CHILD))
            {
                rect = child->GetWindowRect(true);
                if (child->HasFlag(WBS_DOCKING))
                {
                    rect = QRect(windowRect.topLeft() + rect.topLeft(), rect.size());
                    child->RenderSelection(rect, viewport);
                }
                else
                {
                    rect = QRect(clientRect.topLeft() + rect.topLeft(), rect.size());
                    child->RenderSelection(rect, viewport);
                }
            }
        }
    }
}