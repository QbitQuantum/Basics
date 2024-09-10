void VideoDock::popup(const QPoint &p)
{
	if (canPopup)
	{
#ifdef Q_OS_MACOS
		// Move parent of video adjustment widget from native Mac widget to QMenu
		QWidget *videoAdj = (QWidget *)QMPlay2GUI.videoAdjustment;
		QWidget *parent = videoAdj->parentWidget();
		if (parent && qstrcmp(parent->metaObject()->className(), "QMacNativeWidget") == 0)
			videoAdj->setParent(QMPlay2GUI.menuBar->playback->videoFilters->videoAdjustmentMenu);
#endif
		popupMenu->popup(mapToGlobal(p));
	}
}