void DidYouKnowWindow::setVisible(Visible visible)
{
    Window::setVisible(visible);

    if (visible == Visible_true || isWindowVisible())
        loadData();
}