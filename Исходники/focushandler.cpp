void FocusHandler::checkForWindow() const
{
    if (mFocusedWidget)
    {
        Widget *widget = mFocusedWidget->getParent();

        while (widget)
        {
            Window *const window = dynamic_cast<Window*>(widget);

            if (window)
            {
                window->requestMoveToTop();
                break;
            }

            widget = widget->getParent();
        }
    }
}