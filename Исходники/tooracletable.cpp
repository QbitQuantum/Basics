/***********************************************************************************
   Main function for table creation/altering called from tobrowsertable.cpp
   It will call either createTable either alterTable
************************************************************************************/
QString toOracleExtract::migrateTable(toExtract &ext, std::list<QString> &source,
                                      std::list<QString> &destin) const
{
#ifdef DEBUG
    qDebug() << "toOracleExtract::migrateTable source=";
    for (std::list<QString>::iterator i = source.begin(); i != source.end(); i++)
    {
        qDebug() << *i;
    }
    qDebug() << "toOracleExtract::migrateTable destin=";
    for (std::list<QString>::iterator i = destin.begin(); i != destin.end(); i++)
    {
        qDebug() << *i;
    }
#endif


    if (source.empty())
    {
#ifdef DEBUG
        qDebug() << "New table has to be created.";
#endif
        return createTable(destin);
    }
    else
    {
#ifdef DEBUG
        qDebug() << "Existing table is to be modified.";
#endif
        return alterTable(source, destin);
    }
} // migrateTable