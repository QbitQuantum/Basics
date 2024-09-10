    bool ArticleViewPrivate::eventFilter(QObject * obj, QEvent * event)
    {
        //qDebug() << "eventFilter" << obj << event;

        const AbstractBibliographicModel * model = qobject_cast< const AbstractBibliographicModel * >(view ? origin(view->model()) : 0);

        // Only filter the view's events
        if (model && obj == view->viewport()) {
            switch (event->type()) {
            case QEvent::DragMove:
            case QEvent::DragEnter: {
                QDropEvent * e = static_cast< QDropEvent * >(event);
                if ((dropping = model->acceptsDrop(e->mimeData()))) {
                    view->viewport()->update();
                    e->accept();
                } else {
                    e->ignore();
                }
                //qDebug() << "---" << dropping;
                return true;
                break;
            }
            case QEvent::DragLeave:
                dropping = false;
                view->viewport()->update();
                break;
            case QEvent::Drop:
                dropping = false;
                view->viewport()->update();
                break;
            default:
                break;
            }
        }

        return QObject::eventFilter(obj, event);
    }