void tst_QItemDelegate::QTBUG4435_keepSelectionOnCheck()
{
    QStandardItemModel model(3, 1);
    for (int i = 0; i < 3; ++i) {
        QStandardItem *item = new QStandardItem(QLatin1String("Item ") + QString::number(i));
        item->setCheckable(true);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        model.setItem(i, item);
    }
    QTableView view;
    view.setModel(&model);
    view.setItemDelegate(new TestItemDelegate);
    view.show();
    view.selectAll();
    QTest::qWaitForWindowShown(&view);
    QStyleOptionViewItem option;
    option.rect = view.visualRect(model.index(0, 0));
    const int checkMargin = qApp->style()->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, 0) + 1;
    QPoint pos = qApp->style()->subElementRect(QStyle::SE_ViewItemCheckIndicator, &option, 0).center()
                 + QPoint(checkMargin, 0);
    QTest::mouseClick(view.viewport(), Qt::LeftButton, Qt::ControlModifier, pos);
    QTRY_VERIFY(view.selectionModel()->isColumnSelected(0, QModelIndex()));
    QCOMPARE(model.item(0)->checkState(), Qt::Checked);
}