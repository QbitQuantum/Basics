/*
	・ウィンドウ表示を行う
	・既に DockWidget に登録済みの場合は、一旦削除を行い表示を行う
 */
void FormNodeEditorImpl::_showForm(QWidget* pWidget, const QString& rqStr, Qt::DockWidgetAreas allowedDockArea, Qt::DockWidgetArea initDockArea)
{
	int nDockCnt = listDockWidgets.size();
	for (int i = 0; i < nDockCnt; i++) {
		QWidget* pWidgetTmp = listDockWidgets[i]->widget();
		if (pWidgetTmp == pWidget) {
			this->removeDockWidget(listDockWidgets[i]);
			listDockWidgets[i]->setWidget(NULL);
			/* [NOTE]
				一度、DockWidget化した widget を show() しても表示されない問題が発生した。
				その対処として、setParent(NULL) を明示的に行ったところ、show()にて表示できるようになった。
				現在の状態が、pWidgetTmp->isVisibleTo(listDockWidgets[i]) にて true の状態であるため、
				親値を外す必要があると思われる。
			 */
			pWidgetTmp->setParent(NULL);
			listDockWidgets.removeAt(i);
			break;
		}
	}

	if (_isEnableFormDockable) {

		QDockWidget* pDock = new QDockWidget(rqStr, this);

		pDock->setWidget(pWidget);
		pDock->setAllowedAreas(allowedDockArea);
		addDockWidget(initDockArea, pDock, Qt::Horizontal);
		pDock->show();

		listDockWidgets.push_back(pDock);

	} else {
		pWidget->show();
	}
}