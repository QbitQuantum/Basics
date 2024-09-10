void Calendar::initDatabase()
{
    QFile dbFile("data.db");
    if(dbFile.exists())
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("data.db");
        m_db.open();
        qDebug() << "Database oppened.";
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("data.db");
        m_db.open();
        QSqlQuery createTable(m_db);
        createTable.exec("CREATE TABLE events(empty_place TEXT NULL, name TEXT NULL, description TEXT NULL, date_time DATETIME)");
        qDebug() << "Database created.";
    }

    m_sqlTableModel = new QSqlTableModel(this, m_db);
    m_sqlTableModel->setTable("events");
    m_sqlTableModel->setSort(3, Qt::AscendingOrder);
    m_sqlTableModel->select();
}