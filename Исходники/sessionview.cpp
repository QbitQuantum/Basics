void SessionView::showEvent(QShowEvent *event)
{
    Utils::TreeView::showEvent(event);
    selectActiveSession();
    setFocus();
}