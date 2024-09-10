bool CloudView::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == mHeader) {
        static QPoint oldPos;
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *ev = (QMouseEvent *)event;
            oldPos = ev->globalPos();

            return true;

        } else if (event->type() == QEvent::MouseMove) {
            QMouseEvent *ev = (QMouseEvent *)event;
            const QPoint delta = ev->globalPos() - oldPos;

            MainWindow *win = seafApplet->mainWindow();
            win->move(win->x() + delta.x(), win->y() + delta.y());

            oldPos = ev->globalPos();
            return true;
        }

    } else if (obj == mDropArea) {
        if (event->type() == QEvent::DragEnter) {
            QDragEnterEvent *ev = (QDragEnterEvent *)event;
            if (ev->mimeData()->hasUrls() && ev->mimeData()->urls().size() == 1) {
                const QUrl url = ev->mimeData()->urls().at(0);
                if (url.scheme() == "file") {
                    QString path = url.toLocalFile();
#if defined(Q_OS_MAC) && (QT_VERSION <= QT_VERSION_CHECK(5, 4, 0))
                    path = utils::mac::fix_file_id_url(path);
#endif
                    if (QFileInfo(path).isDir()) {
                        ev->acceptProposedAction();
                    }
                }
            }
            return true;
        } else if (event->type() == QEvent::Drop) {
            QDropEvent *ev = (QDropEvent *)event;
            const QUrl url = ev->mimeData()->urls().at(0);
            QString path = url.toLocalFile();
#if defined(Q_OS_MAC) && (QT_VERSION <= QT_VERSION_CHECK(5, 4, 0))
            path = utils::mac::fix_file_id_url(path);
#endif
            ev->setDropAction(Qt::CopyAction);
            ev->accept();
            showCreateRepoDialog(path);
            return true;
        }
    }

    return QWidget::eventFilter(obj, event);
}