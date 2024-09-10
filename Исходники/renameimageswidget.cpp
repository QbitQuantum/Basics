QString RenameImagesWidget::oldToNewName(BatchProcessImagesItem* item, int itemPosition)
{
    KUrl url;
    url.setPath(item->pathSrc());

    QFileInfo fi(item->pathSrc());

    KIPI::ImageInfo info = m_interface->info(url);

    bool useExtraSymbols = ui->m_addFileDateCheck->isChecked() &&
                           ui->m_useExtraSymbolsCheck->isChecked();

    QString newName = ui->m_prefixEdit->text();

    if (ui->m_addFileNameCheck->isChecked())
    {
        newName += fi.baseName();
        newName += '_';
    }

    int seqNumber = itemPosition + ui->m_seqSpin->value();
    if (ui->m_addFileDateCheck->isChecked())
    {
        QString format = ui->m_formatDateEdit->text();
        format         = format.simplified();
        if (useExtraSymbols)
        {
            QRegExp rxI("\\[i(:(\\d+))?\\]");
            QRegExp rxN("\\[([anbBeEp])([-+]?)(:(\\d*|-\\d+)\\.\\.(\\d*|-\\d+))?\\]");

            for (int watchDog = 0; watchDog < 100; watchDog++)
            {
                QString to;
                int j, i = rxI.indexIn(format);
                if (i != -1)
                {
                    j              = rxI.matchedLength();
                    QString digits = rxI.cap(2);
                    int k          = digits.isEmpty() ? 0 : digits.toInt();
                    if (k < 2)
                    {
                        to = QString::number(seqNumber);
                    }
                    else
                    {
                        QString fmt;
                        fmt.sprintf("0%dd", (k > 10 ? 10 : k));
                        fmt = '%' + fmt;
                        to.sprintf(fmt.toLatin1(), seqNumber);
                    }
                }
                else
                {
                    if ((i = rxN.indexIn(format)) == -1)
                    {
                        break;
                    }
                    j            = rxN.matchedLength();
                    QString from = rxN.cap(1);
                    from = (from == "e") ? fi.suffix() :
                           (from == "E") ? fi.completeSuffix() :
                           (from == "b") ? fi.baseName() :
                           (from == "B") ? fi.completeBaseName() :
                           (from == "n") ? fi.fileName() :
                           (from == "a") ? fi.absoluteDir().dirName() :
                           (from == "p") ? fi.absolutePath() :
                           "";
                    int len            = from.length();
                    QString start      = rxN.cap(4);
                    QString end        = rxN.cap(5);
                    int k              = start.isEmpty() ? 1 : start.toInt();
                    int l              = end.isEmpty() ? len : end.toInt();
                    k                  = (k < -len) ? 0 : (k < 0) ? (len + k) : (k > 0) ? (k - 1) : 0;
                    l                  = (l < -len) ? -1 : (l < 0) ? (len + l) : (l > 0) ? (l - 1) : 0;
                    to                 = l < k ? "" : from.mid(k, l - k + 1);
                    QString changeCase = rxN.cap(2);
                    if (!changeCase.isEmpty())
                    {
                        to = (changeCase == "+") ? to.toUpper() : to.toLower();
                    }
                }
                format.replace(i, j, to);
            }
        }
        format.replace("%%", "%");
        format.remove("%s");
        format.replace('/', '!');
        format.replace("%[", "% [");

        time_t time        = info.time().toTime_t();
        struct tm* time_tm = ::localtime(&time);
        char s[100];
        ::strftime(s, 100, QFile::encodeName(format), time_tm);

        newName += QString::fromLocal8Bit(s);
        if (!useExtraSymbols)
        {
            newName += '_';
        }
    }

    if (!useExtraSymbols)
    {
        int numDigits = 1;
        int count = ui->m_listView->topLevelItemCount();
        while (count > 0)
        {
            numDigits++;
            count = count / 10;
        }

        QString format;
        format.sprintf("0%dd", numDigits);
        format = '%' + format;

        QString seq;
        seq.sprintf(format.toLatin1(), seqNumber);
        newName += seq;

        newName += QString::fromLatin1(".") + fi.suffix();
    }

    return newName;
}