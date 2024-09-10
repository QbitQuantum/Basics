int
StarDictDictionaryManager::lookupSimilarWord(QByteArray searchWord, int iLib)
{
    int iIndex;

    // Upper case lookup
    iIndex = d->dictionaryList.at(iLib)->lookup(searchWord.toUpper());

    // Lower case lookup
    if (iIndex == -1)
        iIndex = d->dictionaryList.at(iLib)->lookup(searchWord.toLower());

    // Upper the first character and lower others
    if (!iIndex == -1)
        iIndex = d->dictionaryList.at(iLib)->lookup(QString(QString(searchWord)[0].toUpper()) + searchWord.mid(1).toLower());

    if (isPureEnglish(searchWord))
    {
        QString caseString;
        // If not Found, try other status of searchWord.
        int searchWordLength = searchWord.size();
        bool isUpperCase;
        QByteArray searchNewWord;

        lookupPattern(searchWord, iLib, "S", 1, 1, QString(), false);
        lookupPattern(searchWord, iLib, "ED", 1, 1, QString(), false);
        lookupPattern(searchWord, iLib, "LY", 2, 2, QString(), true);
        lookupPattern(searchWord, iLib, "ING", 3, 3, "E", true);


        if (iIndex == -1 && searchWordLength > 3)
        {
            isUpperCase = (searchWord.endsWith("ES") //krazy:exclude=strings
                        && (searchWord.at(searchWordLength - 3) == 'S'
                        || searchWord.at(searchWordLength - 3) == 'X'
                        || searchWord.at(searchWordLength - 3) == 'O'
                        || (searchWordLength > 4 && searchWord.at(searchWordLength - 3) == 'H'
                        && (searchWord.at(searchWordLength - 4) == 'C'
                        || searchWord.at(searchWordLength - 4) == 'S'))));

            if (isUpperCase ||
                    (searchWord.endsWith("es") //krazy:exclude=strings
                     && (searchWord.at(searchWordLength - 3) == 's'
                     || searchWord.at(searchWordLength - 3) == 'x'
                     || searchWord.at(searchWordLength - 3) == 'o'
                     || (searchWordLength > 4 && searchWord.at(searchWordLength - 3) == 'h'
                     && (searchWord.at(searchWordLength - 4) == 'c'
                     || searchWord.at(searchWordLength - 4) == 's')))))
            {
                searchNewWord = searchWord.left(searchWordLength - 2);
                if ((iIndex = d->dictionaryList.at(iLib)->lookup(searchNewWord)) == -1
                    && (isUpperCase || QString::fromUtf8(searchWord).at(0).isUpper()))
                {
                    caseString = searchNewWord.toLower();
                    if (caseString.compare(searchNewWord))
                    {
                        iIndex = d->dictionaryList.at(iLib)->lookup(caseString);
                    }
                }
            }
        }

        lookupPattern(searchWord, iLib, "ED", 3, 2, QString(), true);
        lookupPattern(searchWord, iLib, "IED", 3, 3, "Y", false);
        lookupPattern(searchWord, iLib, "IES", 3, 3, "Y", false);
        lookupPattern(searchWord, iLib, "ER", 2, 3, QString(), false);
        lookupPattern(searchWord, iLib, "EST", 3, 3, QString(), false);

    }

#if 0
    else
    {
        //don't change iWordIndex here.
        //when LookupSimilarWord all failed too, we want to use the old LookupWord index to list words.
        //iWordIndex = invalidIndex;
    }
#endif
    return iIndex;
}