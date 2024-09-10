// We don't set anything because the data is saved within the view not the model!
void RideDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    // stored as text field
    if (index.column() == dateColumn) {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        QString value = dateEdit->date().toString("dd MMM yyyy");
        // Place in the view
        model->setData(index, value, Qt::DisplayRole);
    } else if (index.column() == dateColumn+1) {
        QTimeEdit *timeEdit = qobject_cast<QTimeEdit *>(editor);
        QString value = timeEdit->time().toString("hh:mm:ss a");
        model->setData(index, value, Qt::DisplayRole);
    }
}