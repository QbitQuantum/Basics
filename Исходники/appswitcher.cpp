void RazorAppSwitcher::SwitcherItem::mouseMoveEvent(QMouseEvent * e)
{
    if (! hasFocus())
        setFocus(Qt::MouseFocusReason);
}