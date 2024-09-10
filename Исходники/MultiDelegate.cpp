void MultiDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QVariant value;

    QString  className = editor->metaObject()->className();
    if (className == "QTimeEdit") {
        QTimeEdit*  ed = qobject_cast<QTimeEdit*>(editor);
        Q_ASSERT( ed);
        value = QVariant( ed->time());
    }
    else if (className == "QDateEdit") {
        QDateEdit*  ed = qobject_cast<QDateEdit*>(editor);
        Q_ASSERT( ed);
        value = QVariant( ed->date());
    }
    else if (className == "QDateTimeEdit") {
        QDateTimeEdit*  ed = qobject_cast<QDateTimeEdit*>(editor);
        Q_ASSERT( ed);
        value = QVariant( ed->dateTime());
    }
    else if (className == "IconViewer") {
        return;
    }
    else if (className == "QComboBox") {
        QComboBox*  ed = qobject_cast<QComboBox*>(editor);
        Q_ASSERT( ed);
        value = QVariant( ed->currentText());
    }
    else if (className == "QListWidget") {
        QListWidget*  ed = qobject_cast<QListWidget*>(editor);
        Q_ASSERT( ed);
        QStringList  valList;
        int  itemCount = ed->count();
        for (int i = 0; i < itemCount; ++i) {
            QListWidgetItem*  bitItem = ed->item(i);
            bool  isChecked = (bitItem->checkState() == Qt::Checked);
            if (isChecked)
                valList += bitItem->text();
        }
        value = QVariant( valList);
    }
    else if (className == "QCheckBox") {
        QCheckBox*  ed = qobject_cast<QCheckBox*>(editor);
        Q_ASSERT( ed);
        value = QVariant( ed->isChecked());
    }
    else {
        QItemDelegate::setModelData( editor, model, index);
        return;
    }
    model->setData(index, value, Qt::EditRole);
}