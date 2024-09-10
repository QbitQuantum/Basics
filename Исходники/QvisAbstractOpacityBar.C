// ****************************************************************************
//  Method:  QvisAbstractOpacityBar::resizeEvent
//
//  Purpose:
//    
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 31, 2001
//
//  Modifications:
//    Brad Whitlock, Fri Jul 18 15:34:34 PDT 2008
//    Qt 4.
//
//    Brad Whitlock, Thu Dec 18 14:09:40 PST 2008
//    I changed how the image gets invalidated.
//
// ****************************************************************************
void
QvisAbstractOpacityBar::resizeEvent(QResizeEvent*)
{
    QRect framerect(rect());
    framerect.setLeft(framerect.left()     +5);
    framerect.setRight(framerect.right()   -10);
    setFrameRect(framerect);

    imageDirty();
    update();
}