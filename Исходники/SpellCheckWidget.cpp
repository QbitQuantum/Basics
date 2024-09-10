void SpellCheckWidget::copyUserDict()
{
    // Get the current dictionary.
    if (!ui.userDictList->selectionModel()->hasSelection()) {
        return;
    }

    int row = ui.userDictList->selectionModel()->selectedIndexes().first().row();
    QStandardItem *item = m_Model.item(row, 1);

    if (!item) {
        return;
    }

    // Get the current words, before creating so list doesn't change
    QStringList words;
    for (int i = 0; i < ui.userWordList->count(); ++i) {
        QString word = ui.userWordList->item(i)->text();
        words.append(word);
    }

    // Create a new dictionary
    QStringList current_dicts;
    for (int row = 0; row < m_Model.rowCount(); ++row) {
        QStandardItem *item = m_Model.itemFromIndex(m_Model.index(row, 1));
        current_dicts.append(item->text());
    }
    QString dict_name = item->text();
    while (current_dicts.contains(dict_name)) {
        dict_name += "_copy";
    }

    if (!createUserDict(dict_name)) {
        return;
    }

    // Add the words to the dictionary
    foreach(QString word, words) {
        QListWidgetItem *item = new QListWidgetItem(word, ui.userWordList);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui.userWordList->addItem(item);
    }