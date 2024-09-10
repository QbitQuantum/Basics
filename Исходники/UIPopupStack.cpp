void UIPopupStack::sltAdjustGeometry()
{
    /* Make sure parent is currently set: */
    if (!parent())
        return;

    /* Read parent geometry: */
    QRect geo(parentWidget()->geometry());
    if (!parentWidget()->isWindow())
        geo.moveTo(parentWidget()->mapToGlobal(QPoint(0, 0)));

    /* Determine size: */
    int iWidth = parentWidget()->width();
    int iHeight = parentWidget()->height();
    /* Subtract menu-bar and status-bar heights: */
    iHeight -= (m_iParentMenuBarHeight + m_iParentStatusBarHeight);
    /* Check if minimum height is even less than current: */
    if (m_pScrollViewport)
    {
        /* Get minimum viewport height: */
        int iMinimumHeight = m_pScrollViewport->minimumSizeHint().height();
        /* Subtract layout margins: */
        int iLeft, iTop, iRight, iBottom;
        m_pMainLayout->getContentsMargins(&iLeft, &iTop, &iRight, &iBottom);
        iMinimumHeight += (iTop + iBottom);
        /* Compare minimum and current height: */
        iHeight = qMin(iHeight, iMinimumHeight);
    }

    /* Determine origin: */
    int iX = 0;
    int iY = 0;
    /* Shift for top-level window: */
    if (isWindow())
    {
        iX += geo.x();
        iY += geo.y();
    }
    switch (m_orientation)
    {
        case UIPopupStackOrientation_Top:
        {
            /* Just add menu-bar height: */
            iY += m_iParentMenuBarHeight;
            break;
        }
        case UIPopupStackOrientation_Bottom:
        {
            /* Shift to bottom: */
            iY += (geo.height() - iHeight);
            /* And subtract status-bar height: */
            iY -= m_iParentStatusBarHeight;
            break;
        }
    }

    /* Adjust geometry: */
    setGeometry(iX, iY, iWidth, iHeight);
}