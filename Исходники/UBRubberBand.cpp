UBRubberBand::enm_resizingMode UBRubberBand::determineResizingMode(QPoint pos)
{
    if (mMouseIsPressed)
        return mResizingMode;
    
    QRect resizerTop    (mResizingBorderHeight               , 0                             , rect().width()-2*mResizingBorderHeight, mResizingBorderHeight                    );
    QRect resizerBottom (mResizingBorderHeight               , rect().height() - mResizingBorderHeight, rect().width()-2*mResizingBorderHeight, mResizingBorderHeight                    );
    QRect resizerLeft   (0                          , mResizingBorderHeight                  , mResizingBorderHeight                 , rect().height() - 2*mResizingBorderHeight);
    QRect resizerRight  (rect().width()-mResizingBorderHeight, mResizingBorderHeight                  , mResizingBorderHeight                 , rect().height() - 2*mResizingBorderHeight);

    QRect resizerTopLeft    (0                          , 0                             , mResizingBorderHeight, mResizingBorderHeight);
    QRect resizerTopRight   (rect().width()-mResizingBorderHeight, 0                             , mResizingBorderHeight, mResizingBorderHeight);
    QRect resizerBottomLeft (0                          , rect().height() - mResizingBorderHeight, mResizingBorderHeight, mResizingBorderHeight);
    QRect resizerBottomRight(rect().width()-mResizingBorderHeight, rect().height() - mResizingBorderHeight, mResizingBorderHeight, mResizingBorderHeight);

    enm_resizingMode resizingMode;
    
    QTransform cursorTransrofm;

    if (resizerTop.contains(pos))
    {
        resizingMode = Top;
        cursorTransrofm.rotate(90);
    }
    else
    if (resizerBottom.contains(pos))
    {
        resizingMode = Bottom;
        cursorTransrofm.rotate(90);
    }
    else
    if (resizerLeft.contains(pos))
    {
        resizingMode = Left;
    }
    else
    if (resizerRight.contains(pos))
    {
        resizingMode = Right;
    }
    else
    if (resizerTopLeft.contains(pos))
    {
        resizingMode = TopLeft;
        cursorTransrofm.rotate(45);
    }
    else
    if (resizerTopRight.contains(pos))
    {
        resizingMode = TopRight;
        cursorTransrofm.rotate(-45);
    }
    else
    if (resizerBottomLeft.contains(pos))
    {
        resizingMode = BottomLeft;
        cursorTransrofm.rotate(-45);
    }
    else
    if (resizerBottomRight.contains(pos))
    {
        resizingMode = BottomRight;
        cursorTransrofm.rotate(45);
    }
    else
        resizingMode = None;
    
    if (None != resizingMode)
    {
        QPixmap pix(":/images/cursors/resize.png");
        QCursor resizeCursor  = QCursor(pix.transformed(cursorTransrofm, Qt::SmoothTransformation), pix.width() / 2,  pix.height() / 2);
        setCursor(resizeCursor);
    }
    else
        unsetCursor();

    return resizingMode;
}