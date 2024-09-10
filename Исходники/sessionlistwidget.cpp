bool SessionListWidget::event(QEvent *event)
{
#ifndef QUTIM_MOBILE_UI
	if (event->type() == QEvent::ToolTip) {
		if (QHelpEvent *help = static_cast<QHelpEvent*>(event)) {
			int index = indexAt(help->pos()).row();
			if (index != -1) {
				ChatUnit *unit = session(index)->getUnit();
				ToolTip::instance()->showText(help->globalPos(), unit, this);
				return true;
			}
		}
	} else if (event->type() == QEvent::DragEnter) {
		QDragEnterEvent *dragEvent = static_cast<QDragEnterEvent*>(event);
		if (const MimeObjectData *data = qobject_cast<const MimeObjectData*>(dragEvent->mimeData())) {
			ChatUnit *u = qobject_cast<ChatUnit*>(data->object());
			if (u)
				dragEvent->acceptProposedAction();
		}
		return true;
	} else if (event->type() == QEvent::Drop) {
		QDropEvent *dropEvent = static_cast<QDropEvent*>(event);
		if (const MimeObjectData *mimeData
				= qobject_cast<const MimeObjectData*>(dropEvent->mimeData())) {
			if (ChatUnit *u = qobject_cast<ChatUnit*>(mimeData->object())) {
				ChatLayerImpl::get(u,true)->activate();
				dropEvent->setDropAction(Qt::CopyAction);
				dropEvent->accept();
				return true;
			}
		}
	} else 
#endif
	if (event->type() == QEvent::ContextMenu) {
		QContextMenuEvent *ev = static_cast<QContextMenuEvent*>(event);
		ChatSessionImpl *s = session(row(itemAt(ev->pos())));
		if(s) {
			s->unit()->showMenu(ev->globalPos());
			return true;
		}

	}
	return QListWidget::event(event);
}