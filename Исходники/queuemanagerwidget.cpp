    void QueueManagerWidget::moveUpClicked()
    {
        QModelIndexList sel = view->selectionModel()->selectedRows();
        QList<int> rows;
        foreach (const QModelIndex& idx, sel)
            rows.append(idx.row());

        if (rows.isEmpty() || rows.front() == 0)
            return;

        model->moveUp(rows.front(), rows.count());

        QItemSelection nsel;
        int cols = model->columnCount(QModelIndex());
        QModelIndex top_left = model->index(rows.front() - 1, 0);
        QModelIndex bottom_right = model->index(rows.back() - 1, cols - 1);
        nsel.select(top_left, bottom_right);
        view->selectionModel()->select(nsel, QItemSelectionModel::Select);
        if (!indexVisible(top_left))
            view->scrollTo(top_left, QAbstractItemView::PositionAtCenter);

        updateButtons();
    }