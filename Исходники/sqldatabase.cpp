void sql_intro_snippets()
{
    {
//! [26]
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("bigblue");
    db.setDatabaseName("flightdb");
    db.setUserName("acarlson");
    db.setPassword("1uTbSbAs");
    bool ok = db.open();
//! [26]
    Q_UNUSED(ok);
    }

    {
//! [27]
    QSqlDatabase firstDB = QSqlDatabase::addDatabase("QMYSQL", "first");
    QSqlDatabase secondDB = QSqlDatabase::addDatabase("QMYSQL", "second");
//! [27]
    }

    {
//! [28]
    QSqlDatabase defaultDB = QSqlDatabase::database();
//! [28] //! [29]
    QSqlDatabase firstDB = QSqlDatabase::database("first");
//! [29] //! [30]
    QSqlDatabase secondDB = QSqlDatabase::database("second");
//! [30]
    }

    {
    // SELECT1
//! [31]
    QSqlQuery query;
    query.exec("SELECT name, salary FROM employee WHERE salary > 50000");
//! [31]

//! [32]
    while (query.next()) {
        QString name = query.value(0).toString();
        int salary = query.value(1).toInt();
        qDebug() << name << salary;
    }
//! [32]
    }

    {
    // FEATURE
//! [33]
    QSqlQuery query;
    int numRows;
    query.exec("SELECT name, salary FROM employee WHERE salary > 50000");

    QSqlDatabase defaultDB = QSqlDatabase::database();
    if (defaultDB.driver()->hasFeature(QSqlDriver::QuerySize)) {
        numRows = query.size();
    } else {
        // this can be very slow
        query.last();
        numRows = query.at() + 1;
    }
//! [33]
    }

    {
    // INSERT1
//! [34]
    QSqlQuery query;
    query.exec("INSERT INTO employee (id, name, salary) "
               "VALUES (1001, 'Thad Beaumont', 65000)");
//! [34]
    }

    {
    // NAMED BINDING
//! [35]
    QSqlQuery query;
    query.prepare("INSERT INTO employee (id, name, salary) "
                  "VALUES (:id, :name, :salary)");
    query.bindValue(":id", 1001);
    query.bindValue(":name", "Thad Beaumont");
    query.bindValue(":salary", 65000);
    query.exec();
//! [35]
    }

    {
    // POSITIONAL BINDING
//! [36]
    QSqlQuery query;
    query.prepare("INSERT INTO employee (id, name, salary) "
                  "VALUES (?, ?, ?)");
    query.addBindValue(1001);
    query.addBindValue("Thad Beaumont");
    query.addBindValue(65000);
    query.exec();
//! [36]
    }

    {
    // UPDATE1
//! [37]
    QSqlQuery query;
    query.exec("UPDATE employee SET salary = 70000 WHERE id = 1003");
//! [37]
    }

    {
    // DELETE1
//! [38]
    QSqlQuery query;
    query.exec("DELETE FROM employee WHERE id = 1007");
//! [38]
    }

    {
    // TRANSACTION
//! [39]
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.exec("SELECT id FROM employee WHERE name = 'Torild Halvorsen'");
    if (query.next()) {
        int employeeId = query.value(0).toInt();
        query.exec("INSERT INTO project (id, name, ownerid) "
                   "VALUES (201, 'Manhattan Project', "
                   + QString::number(employeeId) + ')');
    }
    QSqlDatabase::database().commit();
//! [39]
    }

    {
    // SQLQUERYMODEL1
//! [40]
    QSqlQueryModel model;
    model.setQuery("SELECT * FROM employee");

    for (int i = 0; i < model.rowCount(); ++i) {
        int id = model.record(i).value("id").toInt();
        QString name = model.record(i).value("name").toString();
        qDebug() << id << name;
    }
//! [40]
    }

    {
    // SQLTABLEMODEL1
//! [41]
    QSqlTableModel model;
    model.setTable("employee");
    model.setFilter("salary > 50000");
    model.setSort(2, Qt::DescendingOrder);
    model.select();

    for (int i = 0; i < model.rowCount(); ++i) {
        QString name = model.record(i).value("name").toString();
        int salary = model.record(i).value("salary").toInt();
        qDebug() << name << salary;
    }
//! [41]
    }

    {
    // SQLTABLEMODEL2
    QSqlTableModel model;
    model.setTable("employee");

//! [42]
    for (int i = 0; i < model.rowCount(); ++i) {
        QSqlRecord record = model.record(i);
        double salary = record.value("salary").toInt();
        salary *= 1.1;
        record.setValue("salary", salary);
        model.setRecord(i, record);
    }
    model.submitAll();
//! [42]

    // SQLTABLEMODEL3
    int row = 1;
    int column = 2;
//! [43]
    model.setData(model.index(row, column), 75000);
    model.submitAll();
//! [43]

    // SQLTABLEMODEL4
//! [44]
    model.insertRows(row, 1);
    model.setData(model.index(row, 0), 1013);
    model.setData(model.index(row, 1), "Peter Gordon");
    model.setData(model.index(row, 2), 68500);
    model.submitAll();
//! [44]

//! [45]
    model.removeRows(row, 5);
//! [45] //! [46]
    model.submitAll();
//! [46]
    }
}