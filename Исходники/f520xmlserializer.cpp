QString F520xmlserializer::avarageQuery(F520Status *f520, QString month, SysError &sysErr) {
    QXmlQuery query;
    QString res;
    QString defaultRes;
    QFile xml(f520->getXmlPath());
    if ( ! xml.exists()) {
        xml.setFileName(f520->getXmlPath());
        if ( ! xml.exists()) {
            sysErr = SysError(SysError::F520_CAN_NOT_OPEN_FILE, "F520 Rasource file not exist");
            return "";
        }
    }

    if (!xml.open(QIODevice::ReadOnly | QIODevice::Text)) {
        sysErr = SysError(SysError::F520_RESOUCES_NOT_EXIST, "F520 can not open xml resource file");
        return "";
    }

    QString queryStr = CARICO + "/" + DAYS + "/" + DAY + "[@" + MONTH_VALUE + "='" + month + "']";
    qDebug() << "F520xmlserializer::query: " << queryStr;

    query.setFocus(&xml);
    query.setQuery(queryStr);
    if ( ! query.isValid()) {
        qDebug() << "F520xmlserializer::query query not valid";
        sysErr = SysError(SysError::F520_QUERY_ERROR, "F520 Query is invalid: " + queryStr);
        return "";
    }

    query.evaluateTo(&res);

    queryStr = CARICO + "/" + DAYS + "/" + DAY + "[@" + NAME + "='" + DEFAULT_DAY + "']";
    qDebug() << "F520xmlserializer::query: " << queryStr;
    query.setQuery(queryStr);
    if (!query.isValid()) {
        qDebug() << "F520xmlserializer::query query not valid";
        sysErr = SysError(SysError::F520_QUERY_ERROR, "F520 Query is invalid: " + queryStr);
        return "";
    }
    query.evaluateTo(&defaultRes);

    qDebug() << "F520xmlserializer::query " << res;

    xml.close();

    QDomDocument avarageWatt;
    res.prepend("<" +DAYS +">\n");
    res.append("<\\" + DAYS + ">");
    avarageWatt.setContent("" + res + "");
    QDomNodeList entryNodes = avarageWatt.elementsByTagName(DAY);

    QDomDocument defaultWatt;
    defaultWatt.setContent("" + defaultRes + "");
    QDomNodeList entryDefaultNodes = defaultWatt.elementsByTagName(DAY);


    QList<float> avarage;

    qDebug() << "F520xmlserializer::query avarageWatt: " << defaultWatt.toString();
    int i;
    for (i = 0; i < getDayOfMonth(month.toInt()); i++) {
        QDomElement node;
        if(i < entryNodes.count())
            node = entryNodes.at(i).toElement();
        else
            node = entryDefaultNodes.at(0).toElement();

        QStringList tmpList = node.attribute(WATT).split('.');
        if (tmpList.length() != 24) {
            sysErr = SysError(SysError::F520_RESOURCE_ERROR, "F520 Resouce Error");
            return "";
        }
        for (int index = 0; index < tmpList.length(); index++) {
            if (avarage.length() <= index) {
                avarage.append(tmpList.at(index).toFloat()  / getDayOfMonth(month.toInt()));
            } else {
                avarage[index] += (tmpList.at(index).toFloat() / getDayOfMonth(month.toInt()));
            }
        }
    }

    QString rtn;
    foreach (int element, avarage) {
        rtn += QString::number(element) + '.';
    }