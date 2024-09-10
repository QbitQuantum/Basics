FileToolBar::FileToolBar(ScribusMainWindow* p) : ScToolBar( tr("File"), "File", p)
{
	parent=p;
	addAction(p->scrActions["fileNew"]);
	addAction(p->scrActions["fileOpen"]);
	addAction(p->scrActions["fileSave"]);
	addAction(p->scrActions["fileClose"]);
	addAction(p->scrActions["filePrint"]);
	addAction(p->scrActions["toolsPreflightVerifier"]);
	addAction(p->scrActions["fileExportAsPDF"]);
	fileOpenButtonMenu = new QMenu();
	QToolButton* tb = dynamic_cast<QToolButton*>(widgetForAction(parent->scrActions["fileOpen"]));
	tb->setMenu(fileOpenButtonMenu);
	tb->setPopupMode(QToolButton::DelayedPopup);
}