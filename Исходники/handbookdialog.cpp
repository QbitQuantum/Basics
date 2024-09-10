HandbookDialog::HandbookDialog(QString tableName, QString tableRusName,
                               const QSqlDatabase &database,
                               QWidget *parent,
                               QStringList hiddenColumns):
    m_database(database),
    mHiddenColumns(hiddenColumns),
    QDialog(parent),
    ui(new Ui::HandbookDialog)
{
    ui->setupUi(this);

    ui->label->setText(tableRusName);
    this->setWindowTitle("Редактирование справочника: " + tableRusName);

    QMap<QString, QString> rusFieldNames = DataBaseExpert::fieldTranslationMap(m_database);
    auto ralTablesForFields = DataBaseExpert::ralationTablesForFields(m_database);
    m_record = database.record(tableName);

    QSqlRelationalTableModel * model = new QSqlRelationalTableModel(0, database);
    model->setTable(tableName);
    for (int i = 0; i < m_record.count(); ++i)
    {
        QString fieldName = m_record.fieldName(i);
        if (fieldName.size() > 3 && fieldName.right(3) == "_FK")
        {
            model->setRelation(i, QSqlRelation(ralTablesForFields[fieldName], "UID", "NAME"));
        }
    }
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //model->removeColumn(0);
    model->select();

    for (int i = 0; i < m_record.count(); ++i)
    {
        model->setHeaderData(i, Qt::Horizontal, rusFieldNames[m_record.fieldName(i)]);
        if (mHiddenColumns.contains(m_record.fieldName(i), Qt::CaseInsensitive))
        {
            ui->tableView->setColumnHidden(i, true);
        }
    }

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new MySqlRelationDelegate(ui->tableView));

    for (int i = 0; i < m_record.count(); ++i)
    {
        if (mHiddenColumns.contains(m_record.fieldName(i), Qt::CaseInsensitive))
        {
            ui->tableView->setColumnHidden(i, true);
        }
    }

    connect(ui->btnInsert, &QPushButton::clicked, [model]()
    {
        model->insertRow(model->rowCount());
    });
    connect(ui->btnSave, &QPushButton::clicked, [model]()
    {
        if (!model->submitAll())
            qDebug() << model->lastError().text();
    });
    connect(ui->btnRevert, &QPushButton::clicked, [model]()
    {
        model->revertAll();
    });
    connect(ui->btnExit, &QPushButton::clicked, [this]()
    {
        this->accept();
    });

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);


    connect(ui->tableView, &QTableView::customContextMenuRequested, [this, &tableName, model] (const QPoint& pos)
    {
        QMenu * contextMenu = new QMenu(tr("Выбор действия со строкой"), ui->tableView);

        QAction* insertAction = new QAction(tr("Добавить"), contextMenu);
        contextMenu->addAction(insertAction);
        connect(insertAction, &QAction::triggered, [this, &model] ()
        {
            model->insertRow(model->rowCount());
        });

        QAction * delAction = new QAction(tr("Удалить"), contextMenu);
        contextMenu->addAction(delAction);
        connect(delAction, &QAction::triggered, [this, &pos, &tableName, model] ()
        {
            QPoint transformPos = pos;
            transformPos.setX(20);
            QModelIndex index = ui->tableView->indexAt(transformPos);
            QString recordId = ui->tableView->model()->data(index).toString();
            QSqlQuery query("DELETE FROM " + tableName + " WHERE UID = " + recordId, m_database);
            query,exec();
            model->submitAll();
        });


        contextMenu->exec(ui->tableView->viewport()->mapToGlobal(pos));
    });



//    connect(ui->label_2, &QLabel::linkActivated, [this]()
//    {
//        WebReportDialog dlg(this->ui->label_2->text(), this);
//        dlg.exec();
//    });
}