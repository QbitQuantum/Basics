void SupplierManageWindow::init()
{
    m_model = new QSqlRelationalTableModel(0, core->database()->database());
    bool r = core->databaseQuery()->suppliers(m_model);
    if(!r) {
	errorHandling(DATABASE_ERROR, core->databaseQuery()->lastErrorNumber());
	return;
    }

    //
    int areaSize = m_model->relationModel(idArea)->rowCount();
    if(!areaSize) {
	QMessageBox::critical(0,
	  trUtf8("Datos incompletos"),
	  trUtf8("Debe ingresar al menos un Rubro en:\n"
		 "Panel General -> Rubros"));
	tb_add->setEnabled(false);
    }
    areaUpdateCombo(false);

    //
    proxyModel->setSourceModel(m_model);
    tv_supplier->setModel(proxyModel);
    tv_supplier->verticalHeader()->hide();
    tv_supplier->horizontalHeader()->setResizeMode(Email, QHeaderView::Stretch);

    m_model->setHeaderData(Name, Qt::Horizontal, trUtf8("Nombre"));
    m_model->setHeaderData(idArea, Qt::Horizontal, trUtf8("Rubro"));
    m_model->setHeaderData(Address, Qt::Horizontal, trUtf8("Dirección"));
    m_model->setHeaderData(Location, Qt::Horizontal, trUtf8("Localidad"));
    m_model->setHeaderData(Phone, Qt::Horizontal, trUtf8("Teléfono"));
    m_model->setHeaderData(Fax, Qt::Horizontal, trUtf8("Fax"));
    m_model->setHeaderData(Email, Qt::Horizontal, trUtf8("Mail"));
    m_model->setHeaderData(ContactName, Qt::Horizontal, trUtf8("Nom. Contacto"));
    m_model->setHeaderData(ContactPhone, Qt::Horizontal, trUtf8("Tel. Contacto"));

    tv_supplier->setColumnHidden(id, true);

    if(m_model->rowCount() == 0) {
	tb_edit->setEnabled(false);
	tb_remove->setEnabled(false);
    }

    connect(tb_add, SIGNAL(clicked()),
	    this, SLOT(addSupplier()));
    connect(tb_remove, SIGNAL(clicked()),
	    this, SLOT(removeSupplier()));
    connect(tb_edit, SIGNAL(clicked()),
	    this, SLOT(editSupplier()));
    connect(tv_supplier, SIGNAL(doubleClicked(const QModelIndex &)),
	    this, SLOT(editSupplier()));
    connect(tb_close, SIGNAL(clicked()),
	    this, SLOT(closeWindow()));
    connect(le_filter, SIGNAL(textChanged(const QString &)),
	    this, SLOT(filterChanged(const QString &)));
    connect(le_filter, SIGNAL(returnPressed()),
	    this, SLOT(filterReturnPressed()));
    connect(tb_areaUpdateCombo, SIGNAL(clicked()),
	    this, SLOT(areaUpdate()));
    connect(cb_area, SIGNAL(currentIndexChanged(int)),
	    this, SLOT(areaComboChanged(int)));


    le_filter->setFocus();
}