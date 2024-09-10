void WtEditor::logCallback(void* opaque, const tdchar* tag, enum TdTraceLevel level, const tdchar* message){
	WtEditor* thiz = static_cast<WtEditor*>(opaque);

	QListWidgetItem* item = new QListWidgetItem(thiz->ui.logList);

	item->setText(QString(tag) + " : " + message);

	QColor color;

	switch(level){
	case eTD_LEVEL_VERBOSE:
		color = QColor(127, 127, 127);
		break;
	case eTD_LEVEL_DEBUG:
		color = QColor(255, 255, 255);
		break;
	case eTD_LEVEL_INFO:
		color = QColor(0, 255, 0);
		break;
	case eTD_LEVEL_WARNING:
		color = QColor(255, 100, 100);
		break;
	case eTD_LEVEL_ERROR:
		color = QColor(255, 0, 0);
		break;
	}

	item->setBackgroundColor(QColor(0, 0, 0));
	item->setTextColor(color);

	thiz->ui.logList->addItem(item);

	thiz->ui.logList->scrollToItem(item);
	thiz->ui.logList->setCurrentItem(item);

	if(thiz->ui.logList->count() > 10){
		thiz->ui.logList->removeItemWidget( thiz->ui.logList->item(0) );
		//delete thiz->ui.logList->takeItem(0);
	}
}