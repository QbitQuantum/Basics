void ProvidersEditor::addItem()
{
    Azahar *myDb = new Azahar;
    myDb->setDatabase(db);

    //get selected items from list
    QItemSelectionModel *selectionModel = ui->productsList->selectionModel();
    QModelIndexList indexList = selectionModel->selectedRows(); // pasar el indice que quiera (0=code, 1=name)
    foreach(QModelIndex index, indexList) {
        qulonglong code = index.data().toULongLong(); // product CODE
        ProductInfo pInfo;
        //get product info from db
        pInfo = myDb->getProductInfo(QString::number(code));

        //check if the product to be added is not already there
        if (!myDb->providerHasProduct(m_pInfo.id, code)) {
            qDebug()<<"The product "<<code<<" is not provided by the porvider yet";
            //insert into the db.
            ProductProviderInfo info;
            info.prodId = code;
            info.provId = m_pInfo.id;
            info.price  = pInfo.price;
            myDb->addProductToProvider(info);
        }
    }