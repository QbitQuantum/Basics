QSGNode *FilteredImage::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGSimpleTextureNode *node = static_cast<QSGSimpleTextureNode*>(oldNode);
    QImage *image = !m_filteredImage.isNull() ? &m_filteredImage : &m_image;

    if(image->isNull())
    {
        delete node;
        return 0;
    }

    if (!node)
    {
        node = new QSGSimpleTextureNode();
    }

    if (m_imageChanged || !node->texture())
    {
        m_imageChanged = false;
        delete node->texture();

        node->setTexture(window()->createTextureFromImage(*image));

        node->setRect(0,0,implicitWidth(),implicitHeight());

        node->markDirty(QSGNode::DirtyMaterial | QSGNode::DirtyGeometry);
    }

    return node;
}