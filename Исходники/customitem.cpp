QSGNode *CustomItem::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *updateData)
{
    Q_UNUSED(updateData);

    QSGSimpleTextureNode *textureNode = static_cast<QSGSimpleTextureNode *>(node);
    if (!textureNode) {
        textureNode = new QSGSimpleTextureNode();
        QImage image(":/images/lady.png");
        m_texture = window()->createTextureFromImage(image);
        textureNode->setTexture(m_texture);}
        textureNode->setRect(0, 0, width(), height());
        textureNode->setFiltering(QSGTexture::Linear);

    return textureNode;

}