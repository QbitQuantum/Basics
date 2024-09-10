void ui_module_articulos::update_table_articulos()
{
    //Limipiamos el model anterior
    QAbstractItemModel * anteriorModel = ui->tableView_articulos->model();
    if(anteriorModel)
            delete anteriorModel;

    //Creamos el nuevo model
    QSqlRelationalTableModel * model = new QSqlRelationalTableModel();
    model->setTable(v_articuloProveedor);


  /* model->setRelation(GRUPO,QSqlRelation(e_grupo,pk_grupo,descripcion));
   model->setRelation(MARCA,QSqlRelation(e_marca,pk_marca,descripcion));
    model->setRelation(MEDIDA,QSqlRelation(e_medida,pk_medida,descripcion));
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setFilter("habilitado=1");*/


    for(int i=0;i<num_header;i++)
    {
        model->setHeaderData(i,Qt::Horizontal,tableHeaders[i]);
    }

    if(model->select())
    {

            ui->tableView_articulos->setModel(model);
            ui->busqueda->setTableModel(model);


    }
    else
    {
        qDebug()<<model->query().lastError();
        qDebug()<<model->query().lastQuery();
        QMessageBox::information(this,"Error","Ocurrio un error al cargar la información");
    }

    //Ocultamos columnas
    ui->tableView_articulos->setColumnHidden(GRUPO,true);
    ui->tableView_articulos->setColumnHidden(HABILITADO,true);
    ui->tableView_articulos->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //qDebug()<<model->query().lastQuery()<<endl;
}