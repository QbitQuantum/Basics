void OutputPaneManager::shortcutTriggered()
{
    QAction *action = qobject_cast<QAction*>(sender());
    QTC_ASSERT(action, return);
    int idx = m_actions.indexOf(action);
    QTC_ASSERT(idx != -1, return);
    Core::IOutputPane *outputPane = m_panes.at(idx);
    // Now check the special case, the output window is already visible,
    // we are already on that page but the outputpane doesn't have focus
    // then just give it focus.
    int current = currentIndex();
    if (OutputPanePlaceHolder::isCurrentVisible() && current == idx) {
        if (!outputPane->hasFocus() && outputPane->canFocus())
            outputPane->setFocus();
        else
            slotHide();
    } else {
        // Else do the same as clicking on the button does.
        buttonTriggered(idx);
    }
}