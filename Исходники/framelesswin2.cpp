void FramelessWin2::GetMoveDirect(QPoint cursorPoint)
{
QRect rect = this->rect();
QPoint tl = mapToGlobal(rect.topLeft());
QPoint rb = mapToGlobal(rect.bottomRight());
int x = cursorPoint.x();
int y = cursorPoint.y();
//左上角
if( x-m_padding <= tl.x() && x >= tl.x() && y - m_padding <= tl.y() && y >= tl.y())
{
    m_direct = FramelessWin2::LEFTTOP;
    setCursor(Qt::SizeFDiagCursor);
}
//左下角
else if (x - m_padding <= tl.x() && x > tl.x() && y - m_padding <= rb.y() && y >= rb.y())
{
    m_direct = LEFTDOWN;
    setCursor(Qt::SizeBDiagCursor);
}
//左边
else if (x <= tl.x() + m_padding && x >= tl.x())
{
    m_direct = LEFT;
    setCursor(Qt::SizeHorCursor);
}
//右上角
else if (x <= rb.x() && x + m_padding >= rb.x() && y >= tl.y() && y - m_padding <= tl.y())
{
    m_direct = RIGHTTOP;
    setCursor(Qt::SizeBDiagCursor);
}
//右下角
else if (x <= rb.x() && x + m_padding >= rb.x() && y <= rb.y() && y + m_padding >= rb.y())
{
    m_direct = RIGHTDOWN;
    setCursor(Qt::SizeFDiagCursor);
}
//右边
else if (x <= rb.x() && x + m_padding >= rb.x())
{

    m_direct = RIGHT;
    setCursor(Qt::SizeHorCursor);
}
//上
else if (y > tl.y() && y < tl.y()+m_padding)
{
    m_direct = UP;
    setCursor(Qt::SizeVerCursor);
}
else if (y <= rb.y() && y +  m_padding >= rb.y())
{
    m_direct = DOWN;
    setCursor(Qt::SizeVerCursor);
}
else
{
    m_direct = UNKOWN;
    setCursor(Qt::ArrowCursor);
}
}