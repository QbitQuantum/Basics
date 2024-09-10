void PlastikClient::paintEvent(QPaintEvent *e)
{
    QRegion region = e->region();

    PlastikHandler *handler = Handler();

    if (oldCaption != caption() )
        clearCaptionPixmaps();

    bool active = isActive();
    bool toolWindow = isToolWindow();

    QPainter painter(widget() );

    // often needed coordinates
    QRect r = widget()->rect();

    int r_w = r.width();
//     int r_h = r.height();
    int r_x, r_y, r_x2, r_y2;
    r.getCoords(&r_x, &r_y, &r_x2, &r_y2);
    const int borderLeft = layoutMetric(LM_BorderLeft);
    const int borderRight = layoutMetric(LM_BorderRight);
    const int borderBottom = layoutMetric(LM_BorderBottom);
    const int titleHeight = layoutMetric(LM_TitleHeight);
    const int titleEdgeTop = layoutMetric(LM_TitleEdgeTop);
    const int titleEdgeBottom = layoutMetric(LM_TitleEdgeBottom);
    const int titleEdgeLeft = layoutMetric(LM_TitleEdgeLeft);
    const int titleEdgeRight = layoutMetric(LM_TitleEdgeRight);

    const int borderBottomTop = r_y2-borderBottom+1;
    const int borderLeftRight = r_x+borderLeft-1;
    const int borderRightLeft = r_x2-borderRight+1;
    const int titleEdgeBottomBottom = r_y+titleEdgeTop+titleHeight+titleEdgeBottom-1;

    const int sideHeight = borderBottomTop-titleEdgeBottomBottom-1;

    QRect Rtitle = QRect(r_x+titleEdgeLeft+buttonsLeftWidth(), r_y+titleEdgeTop,
                         r_x2-titleEdgeRight-buttonsRightWidth()-(r_x+titleEdgeLeft+buttonsLeftWidth()),
                         titleEdgeBottomBottom-(r_y+titleEdgeTop) );

    QRect tempRect;

    // topSpacer
    if(titleEdgeTop > 0)
    {
        tempRect.setRect(r_x+2, r_y, r_w-2*2, titleEdgeTop );
        if (tempRect.isValid() && region.contains(tempRect) ) {
            painter.drawTiledPixmap(tempRect, handler->pixmap(qubes_label, TitleBarTileTop, active, toolWindow) );
        }
    }

    // leftTitleSpacer
    int titleMarginLeft = 0;
    int titleMarginRight = 0;
    if(titleEdgeLeft > 0)
    {
        tempRect.setRect(r_x, r_y, borderLeft, titleEdgeTop+titleHeight+titleEdgeBottom);
        if (tempRect.isValid() && region.contains(tempRect) ) {
            painter.drawTiledPixmap(tempRect, handler->pixmap(qubes_label, TitleBarLeft, active, toolWindow) );
            titleMarginLeft = borderLeft;
        }
    }

    // rightTitleSpacer
    if(titleEdgeRight > 0)
    {
        tempRect.setRect(borderRightLeft, r_y, borderRight, titleEdgeTop+titleHeight+titleEdgeBottom);
        if (tempRect.isValid() && region.contains(tempRect) ) {
            painter.drawTiledPixmap(tempRect, handler->pixmap(qubes_label, TitleBarRight, active, toolWindow) );
            titleMarginRight = borderRight;
        }
    }

    // titleSpacer
    const QPixmap &caption = captionPixmap();
    if(Rtitle.width() > 0)
    {
        m_captionRect = captionRect(); // also update m_captionRect!
        if (m_captionRect.isValid() && region.contains(m_captionRect) )
        {
            painter.drawTiledPixmap(m_captionRect, caption);
        }

        // left to the title
        tempRect.setRect(r_x+titleMarginLeft, m_captionRect.top(),
                         m_captionRect.left() - (r_x+titleMarginLeft), m_captionRect.height() );
        if (tempRect.isValid() && region.contains(tempRect) ) {
            painter.drawTiledPixmap(tempRect, handler->pixmap(qubes_label, TitleBarTile, active, toolWindow) );
        }

        // right to the title
        tempRect.setRect(m_captionRect.right()+1, m_captionRect.top(),
                         (r_x2-titleMarginRight) - m_captionRect.right(), m_captionRect.height() );
        if (tempRect.isValid() && region.contains(tempRect) ) {
            painter.drawTiledPixmap(tempRect, handler->pixmap(qubes_label, TitleBarTile, active, toolWindow) );
        }

    }

    // leftSpacer
    if(borderLeft > 0 && sideHeight > 0)
    {
        tempRect.setCoords(r_x, titleEdgeBottomBottom+1, borderLeftRight, borderBottomTop-1);
        if (tempRect.isValid() && region.contains(tempRect) ) {
            painter.drawTiledPixmap(tempRect, handler->pixmap(qubes_label, BorderLeftTile, active, toolWindow) );
        }
    }

    // rightSpacer
    if(borderRight > 0 && sideHeight > 0)
    {
        tempRect.setCoords(borderRightLeft, titleEdgeBottomBottom+1, r_x2, borderBottomTop-1);
        if (tempRect.isValid() && region.contains(tempRect) ) {
            painter.drawTiledPixmap(tempRect, handler->pixmap(qubes_label, BorderRightTile, active, toolWindow) );
        }
    }

    // bottomSpacer
    if(borderBottom > 0)
    {
        int l = r_x;
        int r = r_x2;

        tempRect.setRect(r_x, borderBottomTop, borderLeft, borderBottom);
        if (tempRect.isValid() && region.contains(tempRect) ) {
            painter.drawTiledPixmap(tempRect, handler->pixmap(qubes_label, BorderBottomLeft, active, toolWindow) );
            l = tempRect.right()+1;
        }

        tempRect.setRect(borderRightLeft, borderBottomTop, borderLeft, borderBottom);
        if (tempRect.isValid() && region.contains(tempRect) ) {
            painter.drawTiledPixmap(tempRect, handler->pixmap(qubes_label, BorderBottomRight, active, toolWindow) );
            r = tempRect.left()-1;
        }

        tempRect.setCoords(l, borderBottomTop, r, r_y2);
        if (tempRect.isValid() && region.contains(tempRect) ) {
            painter.drawTiledPixmap(tempRect, handler->pixmap(qubes_label, BorderBottomTile, active, toolWindow) );
        }
    }
}