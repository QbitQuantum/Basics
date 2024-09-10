bool NameItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *, const QStyleOptionViewItem &, const QModelIndex &)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::RightButton) {
            m_TreeModel->openContextMenu(mouseEvent->globalPos());
            mouseEvent->accept();
            return true;
        }
    }
    return false;
}