// =============================================================================
void TableViewDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    // Day belongs to header
    int column = index.column();

    if (column == Col::START_TIME   ||
        column == Col::END_TIME     ||
        column == Col::PAUSE_TIME   ||
        column == Col::REQUIRED_TIME) {

        QTimeEdit *timeEdit = qobject_cast<QTimeEdit *>(editor);
        QTime time = timeEdit->time();
        model->setData(index, time);

    } else {
        QItemDelegate::setModelData(editor, model, index);
    }
}