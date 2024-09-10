void ModeManager::setFocusToCurrentMode()
{
    IMode *mode = currentMode();
    QTC_ASSERT(mode, return);
    QWidget *widget = mode->widget();
    if (widget) {
        QWidget *focusWidget = widget->focusWidget();
        if (focusWidget)
            focusWidget->setFocus();
        else
            widget->setFocus();
    }
}