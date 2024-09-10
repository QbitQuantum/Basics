void WindowBase::setVisible(bool visible)
{
    bool wasVisible = mMainWidget->getVisible();
    mMainWidget->setVisible(visible);

    if (visible)
        onOpen();
    else if (wasVisible)
        onClose();

    // This is needed as invisible widgets can retain key focus.
    // Remove for MyGUI 3.2.2
    if (!visible)
    {
        MyGUI::Widget* keyFocus = MyGUI::InputManager::getInstance().getKeyFocusWidget();
        while (keyFocus != mMainWidget && keyFocus != nullptr)
            keyFocus = keyFocus->getParent();

        if (keyFocus == mMainWidget)
            MWBase::Environment::get().getWindowManager()->setKeyFocusWidget(nullptr);
    }
}