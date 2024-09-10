void GUIApplication::addEventHandler(const String& windowName, const String& eventName, const CEGUI::Event::Subscriber& callback)
{
    Window* wRoot = m_guiContext->getRootWindow();

    if (wRoot->isChild(windowName))
    {
        Window* myWindow = wRoot->getChild(windowName);
        myWindow->subscribeEvent(eventName, callback);
    }
}