/**
 * @brief Quit program, closing all main windows
 *
 * This is currently used only on OSX because of the global menu bar.
 * On other platforms, there may be windows belonging to different processes open,
 * so shutting down the whole process when Quit was chosen from one window may
 * result in inconsistent operation.
 */
void MacMenu::quitAll()
{
	int mainwindows = 0;
	int dirty = 0;
	bool forceDiscard = false;

	for(const QWidget *widget : qApp->topLevelWidgets()) {
		const MainWindow *mw = qobject_cast<const MainWindow*>(widget);
		if(mw) {
			++mainwindows;
			if(!mw->canReplace())
				++dirty;
		}
	}

	if(mainwindows==0) {
		qApp->quit();
		return;
	}

	if(dirty>1) {
		QMessageBox box;
		box.setText(tr("You have %n images with unsaved changes. Do you want to review these changes before quitting?", "", dirty));
		box.setInformativeText(tr("If you don't review your documents, all changes will be lost"));
		box.addButton(tr("Review changes..."), QMessageBox::AcceptRole);
		box.addButton(QMessageBox::Cancel);
		box.addButton(tr("Discard changes"), QMessageBox::DestructiveRole);

		int r = box.exec();

		if(r == QMessageBox::Cancel)
			return;
		else if(r == 1)
			forceDiscard = true;
	}

	qApp->setQuitOnLastWindowClosed(true);

	if(forceDiscard) {
		for(QWidget *widget : qApp->topLevelWidgets()) {
			MainWindow *mw = qobject_cast<MainWindow*>(widget);
			if(mw)
				mw->exit();
		}

	} else {
		qApp->closeAllWindows();
		bool allClosed = true;
		for(QWidget *widget : qApp->topLevelWidgets()) {
			MainWindow *mw = qobject_cast<MainWindow*>(widget);
			if(mw) {
				allClosed = false;
				break;
			}
		}
		if(!allClosed) {
			// user cancelled quit
			qApp->setQuitOnLastWindowClosed(false);
		}
	}
}