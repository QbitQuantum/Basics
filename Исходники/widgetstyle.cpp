void WidgetStyle::distinguishRect(const QRectF& rect)
{
    m_deleteGraphicsWgt_.clear();
    for(GraphicsWidget* wgt : m_scene->getItemWidget())
    {
        if(rect.intersects(wgt->boundingRectToScene()))
        {
            wgt->selectWidget(true);
            m_deleteGraphicsWgt_.push_back(wgt);
        }
        else
        {
            auto iter = qFind(m_deleteGraphicsWgt_.begin(), m_deleteGraphicsWgt_.end(), wgt);
            if(iter != m_deleteGraphicsWgt_.end())
                m_deleteGraphicsWgt_.erase(iter);
            wgt->selectWidget(false);
        }
    }
}