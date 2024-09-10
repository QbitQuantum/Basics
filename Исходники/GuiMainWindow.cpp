void GuiMainWindow::currentChanged(int index)
{
    if (index < 0)
        return;
    if (index < (signed)widgetAtIndex.size()) {
        auto it = widgetAtIndex[index];
        if (it.first) {
            if (it.first->focusWidget())
                it.first->focusWidget()->setFocus();
        } else if (it.second)
            it.second->setFocus();
        return;
    }

    // slow_mode: if tab is inserted just now, widgetAtIndex may not
    // be up-to-date.
    if (tabArea->widget(index)) {
        QWidget *currWgt = tabArea->widget(index);
        if (qobject_cast<GuiSplitter*>(currWgt)) {
            if (currWgt->focusWidget())
                currWgt->focusWidget()->setFocus();
        } else if (qobject_cast<GuiTerminalWindow*>(currWgt))
            currWgt->setFocus();
    }
}