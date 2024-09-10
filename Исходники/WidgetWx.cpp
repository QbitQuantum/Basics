void Widget::paint(GraphicsContext*,const IntRect& r)
{
    invalidateRect(r);
    if (PlatformWidget widget = platformWidget())
        widget->Update();
}