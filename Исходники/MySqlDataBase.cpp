bool MySqlDataBase::insertWithManyValues(const QString &tableDescr,
                                         const QList<QVariantList> &data)
{
    if(data.count() == 0
            || tableDescr.isEmpty())
    {
        return false;
    }
    QSqlQuery query(db_);

    const int bufferSizeMax = 2000;
    int counter = 0;
    const int dataSize = data.at(0).count();

    QString valuesRequet("(");
    for(int i = 0; i < data.count(); i++)
    {
        valuesRequet += "?, ";
    }
    valuesRequet = valuesRequet.left(valuesRequet.length()-2);
    valuesRequet += "),";

    beginTransaction();

    while(counter < dataSize)
    {
        int delta = 0;
        if(counter + bufferSizeMax <= dataSize)
        {
            delta = bufferSizeMax;
        }
        else
        {
            delta = dataSize - counter;
        }

        QString request("insert into " + tableDescr + " values");

        for(int j = counter; j < counter + delta ; j++)
        {
            request += valuesRequet;
        }

        request = request.left(request.length() - 1);
        request += ";";
        query.prepare(request);

        for(int k = counter; k < counter + delta; k++)
        {
            foreach (const QVariantList &list, data)
            {
                query.addBindValue(list.at(k));
            }
        }

        if(!query.exec())
        {
            qInfo() << query.lastError().text();
            qInfo() << query.lastQuery();
            rollbackTransaction();
            return false;
        }

        counter += delta;
    }