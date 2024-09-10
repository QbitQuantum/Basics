/*! This slot should get called when the current tab has
 *  changed.
 */
void UserEventTabDlg::currentChanged(int index)
{
  QWidget* tab = myTabs->widget(index);
  tab->setFocus();  // prevents users from accidentally typing in the wrong widget
  updateTitle(tab);
  clearEvents(tab);
}