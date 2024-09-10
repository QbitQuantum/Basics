bool InternalWindow::takeFocus(bool Temporary)
{

    if(getFocused() &&
       getDrawingSurface() != NULL &&
       getDrawingSurface()->getFocusedWindow() == InternalWindowRefPtr(this))
    {
        return true;
    }
    setFocused(true);
    if(Temporary || getDrawingSurface() == NULL)
    {
        focusGained(FocusEvent::create(ComponentRefPtr(this),getSystemTime(),Temporary, NULL));
    }
    else
    {
        if(getDrawingSurface()->getFocusedWindow() != NULL)
        {
            getDrawingSurface()->getFocusedWindow()->giveFocus(this);
        }
        getDrawingSurface()->setFocusedWindow(this);
        focusGained(FocusEvent::create(ComponentRefPtr(this),getSystemTime(),Temporary, getDrawingSurface()->getFocusedWindow()));
    }
    return true;
}