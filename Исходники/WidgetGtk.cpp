void Widget::invalidate()
{
    invalidateRect(IntRect(0, 0, width(), height()));
}