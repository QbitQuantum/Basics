//---------------------------------------------------------------------------
//  getWordItems
//
//! Construct a list of word items to be inserted into a word list, based on
//! the results of a list of searches.
//
//! @param searchSpecs the list of search specifications
//! @return a list of word items
//---------------------------------------------------------------------------
QList<WordTableModel::WordItem>
WordVariationDialog::getWordItems(const QList<SearchSpec>& searchSpecs) const
{
    QList<WordTableModel::WordItem> wordItems;
    QMap<QString, QString> wordMap;
    QListIterator<SearchSpec> lit (searchSpecs);
    while (lit.hasNext()) {
        QStringList wordList = wordEngine->search(lexicon, lit.next(), false);
        QStringListIterator wit (wordList);
        while (wit.hasNext()) {
            QString str = wit.next();
            wordMap.insert(str.toUpper(), str);
        }
    }

    QMapIterator<QString, QString> mit (wordMap);
    while (mit.hasNext()) {
        mit.next();
        QString value = mit.value();
        QList<QChar> wildcardChars;
        for (int i = 0; i < value.length(); ++i) {
            QChar c = value[i];
            if (c.isLower())
                wildcardChars.append(c);
        }
        QString wildcard;
        if (!wildcardChars.isEmpty()) {
            qSort(wildcardChars.begin(), wildcardChars.end(),
                  Auxil::localeAwareLessThanQChar);
            foreach (const QChar& c, wildcardChars)
                wildcard.append(c.toUpper());
        }
        wordItems.append(WordTableModel::WordItem(
            mit.key(), WordTableModel::WordNormal, wildcard));
    }