void MDragDownView::updateRect()
{
    CCPoint worldPosition = this->convertToWorldSpace(CCPointZero);
    
    float fScaleX = this->getScaleX();
    float fScaleY = this->getScaleY();
    
    for (CCNode *p = m_pParent; p != NULL; p = p->getParent())
    {
        fScaleX *= p->getScaleX();
        fScaleY *= p->getScaleY();
    }
    
    if(fScaleX < 0.f)
    {
        worldPosition.x += m_viewSize.width * fScaleX;
        fScaleX = -fScaleX;
    }
    if(fScaleY < 0.f)
    {
        worldPosition.y += m_viewSize.height * fScaleY;
        fScaleY = -fScaleY;
    }
    
    m_viewRect.setRect(worldPosition.x,
                       worldPosition.y + (m_fViewMaxHeight - m_viewSize.height) * fScaleY,
                       m_viewSize.width * fScaleX,
                       m_viewSize.height * fScaleY);
    
    if (m_pDragBar)
    {
        auto dragSize = m_pDragBar->getContentSize();
        auto dragFixSize = CCSizeMake(dragSize.width * m_pDragBar->getScaleX() * fScaleX,
                                      dragSize.height * m_pDragBar->getScaleY() * fScaleY);
        float fWidth = dragFixSize.width < m_viewRect.size.width ? dragFixSize.width : m_viewRect.size.width;
        float fHeight = dragFixSize.height < m_viewRect.size.height ? dragFixSize.height : m_viewRect.size.height;
        m_dragBarRect.setRect(m_viewRect.origin.x + (m_viewRect.size.width-fWidth)*0.5,
                              m_viewRect.origin.y, fWidth, fHeight);
    }
    /*
    CCLog("[%.0f, %.0f, %.0f, %.0f], [%.0f, %.0f, %.0f, %.0f]",
          m_viewRect.origin.x, m_viewRect.origin.y,
          m_viewRect.size.width, m_viewRect.size.height,
          m_dragBarRect.origin.x, m_dragBarRect.origin.y,
          m_dragBarRect.size.width, m_dragBarRect.size.height);//*/
}