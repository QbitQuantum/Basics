QAccessible::State QAccessibleTable2Cell::state(int child) const
{
    Q_ASSERT(child == 0);
    State st = Normal;

    QRect globalRect = view->rect();
    globalRect.translate(view->mapToGlobal(QPoint(0,0)));
    if (!globalRect.intersects(rect(0)))
        st |= Invisible;

    if (view->selectionModel()->isSelected(m_index))
        st |= Selected;
    if (view->selectionModel()->currentIndex() == m_index)
        st |= Focused;
    if (m_index.model()->data(m_index, Qt::CheckStateRole).toInt() == Qt::Checked)
        st |= Checked;

    Qt::ItemFlags flags = m_index.flags();
    if (flags & Qt::ItemIsSelectable) {
        st |= Selectable;
        st |= Focusable;
        if (view->selectionMode() == QAbstractItemView::MultiSelection)
            st |= MultiSelectable;
        if (view->selectionMode() == QAbstractItemView::ExtendedSelection)
            st |= ExtSelectable;
    }
    if (m_role == QAccessible::TreeItem) {
        const QTreeView *treeView = qobject_cast<const QTreeView*>(view);
        if (treeView->isExpanded(m_index))
            st |= Expanded;
    }
    return st;
}