void DataConnect::collectionInsert(Collection c)
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    QString type = QString::fromStdString(c.getType());
    QString dataType = QString::fromStdString(c.getDataType());
    QString title = QString::fromStdString(c.getTitle());
    QString version = QString::fromStdString(c.getVersion());
//    int idenCode = c.getIdenCode();
    QString publisher = QString::fromStdString(c.getPublisher());
    std::cout << c.getPublisher()<< endl;
    int yearRecored = c.getYearRecored();
    int duration = c.getDuration();
    QString category = QString::fromStdString(c.getCategory());

    QSqlQuery comman;
    QString exc = QString("INSERT INTO collection (type , dataType, title,")
            +QString("version, publisher,yearRecored,duration,category ) VALUES ")
            +QString("('")+ type +QString("','")+dataType+QString("','")+title
            +QString("','")+ version +QString("'")/*+ QString::number(idenCode)*/ +QString(",'")
            +publisher +QString("',")+QString::number(yearRecored)+QString(",")+QString::number(duration)
            +QString(",'") +category+ QString("');");
    std::cout << exc.toStdString()<< std::endl;
    if(comman.exec(exc)) {
        std::cout <<"insert success!\n";
    } else {
        std::cout << "insert failure!\n";
    }
    mydb.close();
}