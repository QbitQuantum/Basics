QSGNode *SvgItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData)
{
    Q_UNUSED(updatePaintNodeData);
    if (!window() || !m_svg) {
        delete oldNode;
        return Q_NULLPTR;
    }

    //this is more than just an optimisation, uploading a null image to QSGAtlasTexture causes a crash
    if (width() == 0 || height() == 0) {
        delete oldNode;
        return Q_NULLPTR;
    }

    ManagedTextureNode *textureNode = static_cast<ManagedTextureNode *>(oldNode);
    if (!textureNode) {
        textureNode = new ManagedTextureNode;
        textureNode->setFiltering(QSGTexture::Linear);
        m_textureChanged = true;
    }

    //TODO use a heuristic to work out when to redraw
    //if !m_smooth and size is approximate simply change the textureNode.rect without
    //updating the material

    if (m_textureChanged || textureNode->texture()->textureSize() != QSize(width(), height())) {
        //despite having a valid size sometimes we still get a null QImage from Plasma::Svg
        //loading a null texture to an atlas fatals
        //Dave E fixed this in Qt in 5.3.something onwards but we need this for now
        if (m_image.isNull()) {
            delete textureNode;
            return Q_NULLPTR;
        }

        QSharedPointer<QSGTexture> texture(window()->createTextureFromImage(m_image, QQuickWindow::TextureCanUseAtlas));
        if (m_smooth) {
            texture->setFiltering(QSGTexture::Linear);
        }
        textureNode->setTexture(texture);
        m_textureChanged = false;

        textureNode->setRect(0, 0, width(), height());
    }

    return textureNode;
}