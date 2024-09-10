QSGNode* QuickSubtitleItem::updatePaintNode(QSGNode *node, UpdatePaintNodeData *data)
{
    Q_UNUSED(data);
    if (m_w_sub == 0 || m_h_sub == 0) {
        return node;
    }
    QSGSimpleTextureNode *stn = static_cast<QSGSimpleTextureNode*>(node);
    if (!node) {
        node = new QSGSimpleTextureNode();
        stn = static_cast<QSGSimpleTextureNode*>(node);
        stn->setFiltering(QSGTexture::Linear);
    }
    stn->setRect(mapSubRect(m_rect, m_w_sub, m_h_sub));
    if (m_texture)
        delete m_texture;
    {
        QMutexLocker lock(&m_mutex);
        Q_UNUSED(lock);
        m_texture = window()->createTextureFromImage(m_image);
    }
    stn->setTexture(m_texture);
    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}