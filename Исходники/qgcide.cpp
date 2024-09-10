QString QDictWidget::searchExpr(const QString &expr, int maxResults)
{
    if(!ensureDictFile())
    {
        return "";
    }
    if(!dictFile.open(QFile::ReadOnly))
    {
        return tr("Unable to open dictionary file ") + dictFile.fileName() + "\n\n" + dictFile.errorString();
    }

    // Start searching from the middle
    qint64 left = 0;
    qint64 right = dictFile.size() - 4096;
    dictFile.seek((left + right) / 2);

    // 0 = find some matching expression
    // 1 = go forward for first matching expr
    // 2 = appending text inside matching entry
    // 3 = skipping text outside entry
    int phase = 0;

    QString exprString("<entry key=\"" + expr);
    char buf[4096];    
    QString result;
    int numResults = 0;
    for(;;)
    {
        int readRes = dictFile.readLine(&buf[0], 4096);
        if(readRes < 0)
        {
            if(dictFile.atEnd())
            {
                break;
            }
            else
            {
                result += tr("Error reading from dictionary file") + ":\n\n" + dictFile.errorString();
            }
            break;
        }
        if(readRes == 0)
        {
            continue;   // empty line
        }
        if(phase == 2)
        {
            QString line(buf);
            int entryEnd = line.indexOf("</entry>");
            if(entryEnd < 0)
            {
                result += line;
                continue;
            }
            result += line.left(entryEnd + 8);
            numResults++;
            if(numResults > maxResults)
            {
                break;
            }
            phase = 3;
            continue;
        }
        char *keyStart = strstr(buf, "<entry key=\"");
        if(keyStart == 0)
        {
            continue;
        }
        keyStart += 12;
        char *keyEnd = strchr(keyStart, '"');
        QString key = QString::fromUtf8(keyStart, keyEnd - keyStart);
        int cmp = compareExprKey(expr, key);
        if(cmp == UNCOMPARABLE_CHARS)
        {
            continue;        // skip uncomparable words
        }
        if(phase == 0)
        {
            bool changed = true;
            if(cmp > 0)      // expression is bigger then key
            {
                left = dictFile.pos();
            }
            else            // expression is smaller or matches
            {
                changed = (right != dictFile.pos());    // comparing twice same word
                right = dictFile.pos();
            }
            if(changed && (right - left > 4096))
            {
                dictFile.seek((left + right) / 2);
                continue;
            }
            phase = 1;
            dictFile.seek(left);
            continue;
        }
        if(phase == 1)
        {
            if(cmp > 0)
            {
                continue;           // first match still not found
            }
            else if(cmp < 0)
            {
                break;              // all matching words passed
            }
            phase = 2;
        }
        if(phase == 2 || phase == 3)
        {
            QString str = QString::fromUtf8(buf);
            int entryStart = str.indexOf(exprString, 0, Qt::CaseInsensitive);
            if(entryStart < 0)
            {
                break;      // first non matching entry was hit
            }
            result += str.right(entryStart - exprString.length());
            phase = 2;
        }
    }
    dictFile.close();
    if(result.length() == 0)
    {
        result = tr("Expression not found");
    }
    return result;
}