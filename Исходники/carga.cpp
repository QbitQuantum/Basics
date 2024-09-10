void Carga::loadCargas(QDate start, QDate end){
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(0, QSqlDatabase::database());

    model->setTable("cargas");
    model->setRelation(2, QSqlRelation("cereales", "id", "cereal"));
    model->setRelation(15, QSqlRelation("transportista", "cuit", "nombre"));
    model->setRelation(8, QSqlRelation("cliente", "cuit", "nombre"));
    model->setRelation(5, QSqlRelation("localizacion", "id", "lugar"));
    model->setRelation(7, QSqlRelation("tipo_operacion", "id", "name"));
    model->setRelation(11, QSqlRelation("boolean", "id", "name"));
    model->setRelation(12, QSqlRelation("boolean", "id", "name"));
    model->setRelation(13, QSqlRelation("boolean", "id", "name"));
    model->setRelation(14, QSqlRelation("boolean", "id", "name"));
    model->setRelation(19, QSqlRelation("boolean", "id", "name"));

    QString filter = "fecha BETWEEN '" + start.toString("yyyy-MM-dd") + "' AND '" + end.toString("yyyy-MM-dd") + "'";

    model->setFilter(filter);

    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Fecha"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Grano"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Cosecha"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Kilos"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Origen"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("N° C porte"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Tipo"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Cliente"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Tarifa a cobrar"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Tarifa a pagar"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Se cobra"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Se paga"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Pagado"));
    model->setHeaderData(14, Qt::Horizontal, QObject::tr("Cobrado"));
    model->setHeaderData(15, Qt::Horizontal, QObject::tr("Transportista"));
    model->setHeaderData(16, Qt::Horizontal, QObject::tr("Observaciones"));
    model->setHeaderData(17, Qt::Horizontal, QObject::tr("Origen"));
    model->setHeaderData(18, Qt::Horizontal, QObject::tr("Destino"));
    model->setHeaderData(19, Qt::Horizontal, QObject::tr("En depósito"));


    model->select();

    ui->cargas->setModel(model);
    ui->cargas->setItemDelegate(new QSqlRelationalDelegate(ui->cargas));
    ui->cargas->setSortingEnabled(true);

    ui->cargas->setVisible(false);
    ui->cargas->resizeColumnsToContents();
    ui->cargas->setVisible(true);

    // OCULTAR COLUMNAS CARGAS
    ui->cargas->setColumnHidden(0,true);

    ui->pushButton_3->setDisabled(true);

}