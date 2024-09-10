QSGNode* QIconItem::updatePaintNode(QSGNode* node, QQuickItem::UpdatePaintNodeData* /*data*/)
{
    if (m_icon.isNull()) {
        delete node;
        return Q_NULLPTR;
    }

    if (m_changed || node == 0) {
        m_changed = false;

        ManagedTextureNode* mNode = dynamic_cast<ManagedTextureNode*>(node);
        if(!mNode) {
            delete node;
            mNode = new ManagedTextureNode;
        }

        QIcon::Mode mode;
        switch(m_state) {
            case DefaultState:
                mode = QIcon::Normal;
                break;
            case ActiveState:
                mode = QIcon::Active;
                break;
            case DisabledState:
                mode = QIcon::Disabled;
                break;
            case SelectedState:
                mode = QIcon::Selected;
                break;
        }

        QImage img;
        const QSize size(width(), height());
        if (!size.isEmpty()) {
            img = m_icon.pixmap(size, mode, QIcon::On).toImage();
        }
        mNode->setTexture(s_iconImageCache->loadTexture(window(), img));
        mNode->setRect(QRect(QPoint(0,0), size));
        node = mNode;
    }

    return node;
}