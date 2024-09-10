QSGNode *FrameSvgItem::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    if (!window() || !m_frameSvg ||
            (!m_frameSvg->hasElementPrefix(m_frameSvg->actualPrefix()) && !m_frameSvg->hasElementPrefix(m_prefix))) {
        delete oldNode;
        return Q_NULLPTR;
    }

    if (m_fastPath) {
        if (m_textureChanged) {
            delete oldNode;
            oldNode = 0;
        }

        if (!oldNode) {
            QString prefix = m_frameSvg->actualPrefix();
            oldNode = new FrameNode(prefix, m_frameSvg);

            bool tileCenter = (m_frameSvg->hasElement(QStringLiteral("hint-tile-center"))
                               || m_frameSvg->hasElement(prefix % QLatin1String("hint-tile-center")));
            bool stretchBorders = (m_frameSvg->hasElement(QStringLiteral("hint-stretch-borders"))
                                   || m_frameSvg->hasElement(prefix % QLatin1String("hint-stretch-borders")));
            FrameItemNode::FitMode borderFitMode = stretchBorders ? FrameItemNode::Stretch : FrameItemNode::Tile;
            FrameItemNode::FitMode centerFitMode = tileCenter ? FrameItemNode::Tile: FrameItemNode::Stretch;

            new FrameItemNode(this, FrameSvg::NoBorder, centerFitMode, oldNode);
            new FrameItemNode(this, FrameSvg::TopBorder | FrameSvg::LeftBorder, FrameItemNode::FastStretch, oldNode);
            new FrameItemNode(this, FrameSvg::TopBorder | FrameSvg::RightBorder, FrameItemNode::FastStretch, oldNode);
            new FrameItemNode(this, FrameSvg::TopBorder, borderFitMode, oldNode);
            new FrameItemNode(this, FrameSvg::BottomBorder, borderFitMode, oldNode);
            new FrameItemNode(this, FrameSvg::BottomBorder | FrameSvg::LeftBorder, FrameItemNode::FastStretch, oldNode);
            new FrameItemNode(this, FrameSvg::BottomBorder | FrameSvg::RightBorder, FrameItemNode::FastStretch, oldNode);
            new FrameItemNode(this, FrameSvg::LeftBorder,  borderFitMode, oldNode);
            new FrameItemNode(this, FrameSvg::RightBorder, borderFitMode, oldNode);

            m_sizeChanged = true;
            m_textureChanged = false;
        }

        if (m_sizeChanged) {
            FrameNode* frameNode = static_cast<FrameNode*>(oldNode);
            QSize frameSize(width(), height());
            QRect geometry = frameNode->contentsRect(frameSize);
            for(int i = 0; i<oldNode->childCount(); ++i) {
                FrameItemNode* it = static_cast<FrameItemNode*>(oldNode->childAtIndex(i));
                it->reposition(geometry, frameSize);
            }

            m_sizeChanged = false;
        }
    } else {
        ManagedTextureNode *textureNode = dynamic_cast<ManagedTextureNode *>(oldNode);
        if (!textureNode) {
            delete oldNode;
            textureNode = new ManagedTextureNode;
            textureNode->setFiltering(QSGTexture::Nearest);
            m_textureChanged = true; //force updating the texture on our newly created node
            oldNode = textureNode;
        }

        if ((m_textureChanged || m_sizeChanged) || textureNode->texture()->textureSize() != m_frameSvg->size()) {
            QImage image = m_frameSvg->framePixmap().toImage();
            textureNode->setTexture(s_cache->loadTexture(window(), image));
            textureNode->setRect(0, 0, width(), height());

            m_textureChanged = false;
            m_sizeChanged = false;
        }
    }

    return oldNode;
}