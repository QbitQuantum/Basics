void BAbstractFileType::showAutocompletionMenu(BAbstractCodeEditorDocument *doc, QTextCursor cursor, const QPoint &)
{
    if (cursor.isNull())
        return;
    QCompleter *completer = doc->findChild<QCompleter *>("beqt/completer");
    cursor.select(QTextCursor::WordUnderCursor);
    if (!cursor.hasSelection()) {
        if (completer)
            completer->popup()->hide();
        return;
    }
    QList<AutocompletionItem> list = createAutocompletionItemList(doc, cursor);
    if (list.isEmpty()) {
        if (completer)
            completer->popup()->hide();
        return;
    }
    QStandardItemModel *model = doc->findChild<QStandardItemModel *>("beqt/completion_model");
    if (!model) {
        model = new QStandardItemModel(doc);
        model->setObjectName("beqt/completion_model");
        model->setColumnCount(1);
    }
    model->clear();
    foreach (const AutocompletionItem &item, list) {
        QStandardItem *si = new QStandardItem(item.actionIcon, item.actionText);
        si->setData(item.actionToolTip, Qt::ToolTipRole);
        si->setData(item.text, Qt::UserRole);
        model->appendRow(si);
    }