void IrcMainWindow::onSelectionChanged()
{
    QTreeWidgetItem *item = ircSessionTreeView->currentItem();
    if(item == NULL) return;
    item->setTextColor(0, QColor(0,0,0));
    if(item->parent() == NULL)
	emit this->selectionChanged(item->text(0));
    else
	emit this->selectionChanged(item->parent()->text(0),
				    item->text(0));
    ircTextInput->setFocus(Qt::OtherFocusReason);
    ircTextView->verticalScrollBar()->setValue(
	    ircTextView->verticalScrollBar()->maximum());
}