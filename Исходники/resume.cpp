void ResumeDialog::itemClicked(const QModelIndex &index)
{
  enableButtonOk(false);
  ui->contentTable->clearContents();
  ui->contentTable->setRowCount(0);
  pList.clear();
  soList.clear();

  trNumber       = trModel->record(index.row()).value("id").toULongLong();
  qDebug()<<"==> selected ticket number:"<<trNumber;
  Azahar *myDb = new Azahar;
  myDb->setDatabase(db);
  TransactionInfo tInfo = myDb->getTransactionInfo(trNumber);
  clientId = tInfo.clientid;
  trDate   = tInfo.date;
  trTime   = tInfo.time;
  QStringList _pList = tInfo.itemlist.split(",");
  QStringList _soList= tInfo.specialOrders.split(",");
  int count = 0;
  //first iterate each product/group
  foreach(QString str, _pList) {
    qulonglong code = str.section('/',0,0).toULongLong();
    double     qty  = str.section('/',1,1).toDouble();
    if (code <= 0 ) break;
    count++;
    ProductInfo pInfo = myDb->getProductInfo(QString::number(code));
    pInfo.qtyOnList = qty;
    pList << pInfo;
    //NOTE:Check for product Availability ??
    //insert to the cntent table
    int rowCount = ui->contentTable->rowCount();
    ui->contentTable->insertRow(rowCount);
    ui->contentTable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(qty)));
    ui->contentTable->setItem(rowCount, 1, new QTableWidgetItem(pInfo.desc));
  }