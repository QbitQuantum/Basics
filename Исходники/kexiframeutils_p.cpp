//! @todo add more frame types
void ClassName::drawFrame(QPainter *p)
{
    if (frameShape() == QFrame::Box) {
        if (frameShadow() == Plain)
            qDrawPlainRect(p, frameRect(), d->frameColor, lineWidth());
        else
            qDrawShadeRect(p, frameRect(), palette(), frameShadow() == QFrame::Sunken,
                           lineWidth(), midLineWidth());
    } else {
        SuperClassName::drawFrame(p);
    }
}