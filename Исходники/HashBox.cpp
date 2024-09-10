bool HashBox::eventFilter(QObject* object, QEvent* event)
{
	if (object == dropWidget) {
		if (event->type() == QEvent::DragEnter) {
			QDragEnterEvent* dragEnterEvent = static_cast<QDragEnterEvent*>(event);
			if (dragEnterEvent) {
				/* print out mimeType */
				showFormats("HashBox::dragEnterEvent", dragEnterEvent->mimeData()->formats());

				if (dragEnterEvent->mimeData()->hasUrls()) {
					std::cerr << "HashBox::dragEnterEvent() Accepting Urls" << std::endl;
					dragEnterEvent->acceptProposedAction();
				} else {
					std::cerr << "HashBox::dragEnterEvent() No Urls" << std::endl;
				}
			}
		} else if (event->type() == QEvent::Drop) {
			QDropEvent* dropEvent = static_cast<QDropEvent*>(event);
			if (dropEvent) {
				if (Qt::CopyAction & dropEvent->possibleActions()) {
					/* print out mimeType */
					showFormats("HashBox::dropEvent", dropEvent->mimeData()->formats());

					QStringList files;

					if (dropEvent->mimeData()->hasUrls()) {
						std::cerr << "HashBox::dropEvent() Urls:" << std::endl;

						QList<QUrl> urls = dropEvent->mimeData()->urls();
						QList<QUrl>::iterator uit;
						for (uit = urls.begin(); uit != urls.end(); ++uit) {
							QString localpath = uit->toLocalFile();
							std::cerr << "Whole URL: " << uit->toString().toStdString() << std::endl;
							std::cerr << "or As Local File: " << localpath.toStdString() << std::endl;

							if (localpath.isEmpty() == false) {
								//Check that the file does exist and is not a directory
								QDir dir(localpath);
								if (dir.exists()) {
									std::cerr << "HashBox::dropEvent() directory not accepted." << std::endl;
									QMessageBox mb(tr("Drop file error."), tr("Directory can't be dropped, only files are accepted."), QMessageBox::Information, QMessageBox::Ok, 0, 0, this);
									mb.exec();
								} else if (QFile::exists(localpath)) {
									files.push_back(localpath);
								} else {
									std::cerr << "HashBox::dropEvent() file does not exists."<< std::endl;
									QMessageBox mb(tr("Drop file error."), tr("File not found or file name not accepted."), QMessageBox::Information, QMessageBox::Ok, 0, 0, this);
									mb.exec();
								}
							}
						}
					}

					addAttachments(files,mDefaultTransferFlags);

					dropEvent->setDropAction(Qt::CopyAction);
					dropEvent->accept();
				} else {
					std::cerr << "HashBox::dropEvent() Rejecting uncopyable DropAction" << std::endl;
				}
			}
		}
	}
	// pass the event on to the parent class
	return QScrollArea::eventFilter(object, event);
}