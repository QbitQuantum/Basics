void TabbedWidget::tabChanged(const int &index)
{
	// A new tab has been selected, so give the focus to its widget
	QWidget* widget = mTabWidget->widget(index);
	if (widget)
		widget->setFocus();
}