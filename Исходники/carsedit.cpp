void CarsEdit::FillTable()
{
    QString str_oper = "SELECT hm_cars.id, hm_cars.name, hm_cars.speed, hm_fuel.name, hm_fuel.id FROM hm_cars INNER JOIN hm_fuel ON hm_cars.fuel_id = hm_fuel.id;";
    QSqlQueryModel * model_Oper = new QSqlQueryModel(0);
    model_Oper->setQuery(str_oper);
    model_Oper->setHeaderData(1, Qt::Horizontal, QObject::trUtf8("Название автомобиля"));
    model_Oper->setHeaderData(2, Qt::Horizontal, QObject::trUtf8("Максимальная скорость"));
    model_Oper->setHeaderData(3, Qt::Horizontal, QObject::trUtf8("Тип топлива"));
    ui->tableView->setModel(model_Oper);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(4);

    QSqlRelationalTableModel *comboModel = new QSqlRelationalTableModel(0);
    comboModel->setTable("hm_fuel");
    int comboIndex = comboModel->fieldIndex("id");
    comboModel->setRelation(comboIndex, QSqlRelation("hm_fuel", "id", "name"));
    comboModel->select();
    QSqlTableModel *comboRelModel = comboModel->relationModel(comboIndex);
    ui->comboBox->setModel(comboRelModel);
    ui->comboBox->setModelColumn(comboRelModel->fieldIndex("name"));
}