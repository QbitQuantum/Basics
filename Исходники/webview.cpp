void WebViewCache::draw(QPainter * painter, QGraphicsEffectSource * source)
{
    const QGraphicsItem *item = source->graphicsItem();

    QSizeF itemSize = item->boundingRect().size();

    if (!qFuzzyCompare(itemSize.width(), m_itemSize.width()) ||
            !qFuzzyCompare(itemSize.height(), m_itemSize.height())) {
        qDebug() << "Refresh tile cache, for new size" << itemSize;

        for (int i = 0; i < m_tilePixmaps.size(); i++) {
            QPixmapCache::remove(m_tilePixmaps[i]);
        }

        m_tilePixmaps.clear();
        m_tileRects.clear();

        int itemWidth = itemSize.width() + 0.5;
        int itemHeight = itemSize.height() + 0.5;

        int tilesX = itemWidth / TileSideLength;
        int tilesY = itemHeight / TileSideLength;

        if ((itemWidth % TileSideLength) != 0) {
            ++tilesX;
        }

        if ((itemHeight % TileSideLength) != 0) {
            ++tilesY;
        }

        int tilesCount = tilesX * tilesY;

        m_tilePixmaps.resize(tilesCount);
        m_tileRects.resize(tilesCount);

        for (int i = 0; i < tilesX; i++) {
            for (int j = 0; j < tilesY; j++) {
                int x = i * TileSideLength;
                int y = j * TileSideLength;
                
                m_tileRects[i + j * tilesX] 
                    = QRectF(x, y, TileSideLength, TileSideLength);
            }
        }

        m_itemSize = itemSize;
    }

    const QGraphicsItem *parentItem = item->parentItem();
    QPointF itemPos = item->pos();
    QRectF parentRect = parentItem->boundingRect();

    for (int i = 0; i < m_tileRects.size(); i++) {
        QRectF tileRect = m_tileRects[i].translated(itemPos);

        if (!tileRect.intersects(parentRect) && !tileRect.contains(parentRect)) {
            continue;
        }

        QPixmap tilePixmap;

        if (!QPixmapCache::find(m_tilePixmaps[i], &tilePixmap)) {
            tilePixmap = QPixmap(TileSideLength, TileSideLength);

            QWebFrame *webFrame = m_webView->page()->mainFrame();

            QPainter tilePainter(&tilePixmap); 
            tilePainter.translate(-m_tileRects[i].left(), -m_tileRects[i].top());
            webFrame->render(&tilePainter, m_tileRects[i].toRect());
            tilePainter.end();

            m_tilePixmaps[i] = QPixmapCache::insert(tilePixmap);
        } 

        tileRect = tileRect.translated(-itemPos);

        painter->drawPixmap(tileRect.topLeft(), tilePixmap);
    }
}