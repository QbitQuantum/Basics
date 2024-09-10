void Pane::focusQuickSearch()
{
  Widget *widget = currentMessageListViewWidget();
  if ( widget ) {
    KLineEdit *quickSearch = widget->quickSearch();
    if ( quickSearch )
      quickSearch->setFocus();
  }
}