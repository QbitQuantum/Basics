void EvictionWindow::on_searchBtn_clicked()
{
    DataBase db;
    db.connectionOpen();

    QSqlQuery query;
    QString searchText = ui->searchEdit->text();
    if(searchText == ""){
        query.prepare("select * from clients");
    } else if(ui->searchType->currentText() == "Номеру комнаты") {
        query.prepare("select * from clients where roomNumber=" + searchText);
    } else if(ui->searchType->currentText() == "Имени") {
        query.prepare("select * from clients where firstName like '%" + searchText + "%'");
    } else if(ui->searchType->currentText() == "Фамилии") {
        query.prepare("select * from clients where lastName like '%" + searchText + "%'");
    } else if(ui->searchType->currentText() == "Паспорту") {
        query.prepare("select * from clients where passport like '%" + searchText + "%'");
    }
    query.exec();

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery(query);
    model->QSqlQueryModel::setHeaderData(0, Qt::Horizontal, "ID");
    model->QSqlQueryModel::setHeaderData(1, Qt::Horizontal, "Имя");
    model->QSqlQueryModel::setHeaderData(2, Qt::Horizontal, "Фамилия");
    model->QSqlQueryModel::setHeaderData(3, Qt::Horizontal, "Паспорт");
    model->QSqlQueryModel::setHeaderData(4, Qt::Horizontal, "Количество дней");
    model->QSqlQueryModel::setHeaderData(5, Qt::Horizontal, "Дата посления");
    model->QSqlQueryModel::setHeaderData(6, Qt::Horizontal, "№ комнаты");
    model->QSqlQueryModel::setHeaderData(7, Qt::Horizontal, "Тип комнаты");
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnToContents(4);
    ui->tableView->resizeColumnToContents(5);

    db.connectionClose();
}