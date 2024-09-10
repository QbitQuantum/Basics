void Parser131500ComAu::parseSearchJourney(QNetworkReply *networkReply)
{
    lastJourneyResultList = new JourneyResultList();

    QBuffer *filebuffer = new QBuffer();
    filebuffer->setData(networkReply->readAll());

    QRegExp regexp = QRegExp("<div class=\"midcolumn3\">(.*)</div>(.*)</div>(.*)<div id=\"righttools\">");
    regexp.setMinimal(true);

    regexp.indexIn(filebuffer->buffer());

    QString element = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><html xmlns=\"http://www.w3.org/1999/xhtml\">\n<body>\n" + regexp.cap(0) + "\n</div></body>\n</html>\n";

    QRegExp imgReg = QRegExp("icon_(.*)_s.gif\" />");
    imgReg.setMinimal(true);
    element.replace(imgReg, "icon_" + QString("\\1") + "_s.gif\" />" + QString("\\1"));
    element.replace("am+", "am");
    element.replace("pm+", "pm");

    //qDebug()<<element;

    QBuffer readBuffer;
    readBuffer.setData(element.toAscii());
    readBuffer.open(QIODevice::ReadOnly);

    QXmlQuery query;
    query.bindVariable("path", &readBuffer);
    query.setQuery("declare default element namespace \"http://www.w3.org/1999/xhtml\"; declare variable $path external; doc($path)/html/body/div/div/table/tbody/tr/td[@id='header2']/string()");

    QStringList departResult;
    if (!query.evaluateTo(&departResult))
    {
        qDebug() << "parser131500ComAu::getJourneyData - Query 1 Failed";
    }

    query.setQuery("declare default element namespace \"http://www.w3.org/1999/xhtml\"; declare variable $path external; doc($path)/html/body/div/div/table/tbody/tr/td[@id='header3']/string()");

    QStringList arriveResult;
    if (!query.evaluateTo(&arriveResult))
    {
        qDebug() << "parser131500ComAu::getJourneyData - Query 2 Failed";
    }

    query.setQuery("declare default element namespace \"http://www.w3.org/1999/xhtml\"; declare variable $path external; doc($path)/html/body/div/div/table/tbody/tr/td[@id='header4']/string()");

    QStringList timeResult;
    if (!query.evaluateTo(&timeResult))
    {
        qDebug() << "parser131500ComAu::getJourneyData - Query 3 Failed";
    }

    query.setQuery("declare default element namespace \"http://www.w3.org/1999/xhtml\"; declare variable $path external; doc($path)/html/body/div/div/table/tbody/tr/td[@id='header5']/string()");

    QStringList trainResult;
    if (!query.evaluateTo(&trainResult))
    {
        qDebug() << "parser131500ComAu::getJourneyData - Query 4 Failed";
    }

    query.setQuery("declare default element namespace \"http://www.w3.org/1999/xhtml\"; declare variable $path external; doc($path)/html/body/div/div/div/string()");

    QStringList headerResult;
    if (!query.evaluateTo(&headerResult))
    {
        qDebug() << "parser131500ComAu::getJourneyData - Query 5 Failed";
    }

    for (int i = 0; i < headerResult.count(); i++) {
        QRegExp regexp = QRegExp("(From:|To:|When:)(.*)$");
        regexp.setMinimal(true);
        regexp.indexIn(headerResult[i].trimmed());
        if (regexp.cap(1) == "From:") {
            lastJourneyResultList->setDepartureStation(regexp.cap(2).trimmed());
        }
        if (regexp.cap(1) == "To:") {
            lastJourneyResultList->setArrivalStation(regexp.cap(2).trimmed());
        }
        if (regexp.cap(1) == "When:") {
            lastJourneyResultList->setTimeInfo(regexp.cap(2).trimmed());
        }
    }

    QRegExp regexp2 = QRegExp("(.*), (\\d\\d) (.*) (\\d\\d\\d\\d)");
    regexp2.setMinimal(true);
    regexp2.indexIn(lastJourneyResultList->timeInfo().trimmed());
    QLocale enLocale = QLocale(QLocale::English, QLocale::UnitedStates);
    int month = 1;
    for (month = 1; month < 10; month++) {
        if (regexp2.cap(3).trimmed() == enLocale.standaloneMonthName(month)) {
            break;
        }
    }

    QDate journeydate = QDate::fromString(regexp2.cap(2).trimmed() + " " + QString::number(month) + " " + regexp2.cap(4).trimmed(), "dd M yyyy");

    //Generate Details search results

    QStringList detailsResult;

    regexp = QRegExp("<table class=\"dataTbl widthcol2and3\" cellspacing=\"0\" style=\"margin:0px ! important;border-right:0px none;\" summary=\"Search Results Details\">(.*)</table>");
    regexp.setMinimal(true);
    int pos = 0;

    while ((pos = regexp.indexIn(filebuffer->buffer(), pos)) != -1) {
        QString element = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><html xmlns=\"http://www.w3.org/1999/xhtml\">\n<body><table>\n" + regexp.cap(1) + "\n</table></body>\n</html>\n";
        element.replace("&nbsp;", " ");
        element.replace("bulletin.gif\">", "bulletin.gif\" />");

        QBuffer readBuffer;
        readBuffer.setData(element.toAscii());
        readBuffer.open(QIODevice::ReadOnly);

        QXmlQuery query;
        query.bindVariable("path", &readBuffer);

        query.setQuery("declare default element namespace \"http://www.w3.org/1999/xhtml\"; declare variable $path external; doc($path)/html/body/table/tbody/tr/td[@headers='header2']/string()");

        QStringList detailsContentResult;
        if (!query.evaluateTo(&detailsContentResult))
        {
            qDebug() << "parser131500ComAu::getJourneyData - DetailsQuery 1 Failed";
        }

        detailsResult << detailsContentResult.join("<linesep>");

        pos += regexp.matchedLength();
    }

    //qDebug()<<departResult;

    //Create search result
    for (int i = 0; i < departResult.count(); i++) {

        //Parse transporttypes and changes
        QString tmp = trainResult[i].trimmed();
        tmp.replace("\t", " ");
        tmp.replace("\n", " ");
        tmp.replace("\r", " ");
        QStringList trains = tmp.split(" ", QString::SkipEmptyParts);
        int changes = trains.length() - 1;
        trains.removeDuplicates();

        //Parse travel time
        tmp = timeResult[i].trimmed();
        tmp.replace("mins", "");
        tmp.replace("min", "");
        tmp.replace("hrs ", ":");
        tmp.replace("hr ", ":");
        QStringList durationLst = tmp.split(":", QString::SkipEmptyParts);

        QString durationStr = "";
        if (durationLst.length() == 1) {
            durationStr.sprintf("00: %02d", durationLst[0].toInt());
        }
        if (durationLst.length() == 2) {
            durationStr.sprintf("%02d:%02d", durationLst[0].toInt(), durationLst[1].toInt());
        }

        JourneyResultItem *item = new JourneyResultItem();
        item->setDate(journeydate);
        item->setId(QString::number(i));
        item->setTransfers(QString::number(changes));
        item->setDuration(durationStr);
        item->setTrainType(trains.join(", "));
        item->setDepartureTime(QTime::fromString(departResult[i].trimmed(), "h:map").toString("hh:mm"));
        item->setArrivalTime(QTime::fromString(arriveResult[i].trimmed(), "h:map").toString("hh:mm"));
        item->setInternalData1(detailsResult[i]);

        lastJourneyResultList->appendItem(item);
    }

    emit journeyResult(lastJourneyResultList);
}