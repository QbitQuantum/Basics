QSGNode *ServerBufferItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    updateTexture();
    QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode *>(oldNode);

    if (!node) {
        node = new QSGSimpleTextureNode();
    }

    node->setTexture(m_provider->texture());

    if (isYInverted()) {
        node->setRect(0, height(), width(), -height());
    } else {
        node->setRect(0, 0, width(), height());
    }

    return node;
}