void PopupMenu::cancel(void)
{
    if(getVisible())
    {
        clearSelection();
            setVisible(false);
        producePopupMenuCanceled(PopupMenuEvent::create(PopupMenuRefPtr(this), getSystemTime()));
    }
}