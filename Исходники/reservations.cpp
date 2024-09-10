void ReservationsDialog::itemClicked(const QModelIndex &index)
{
  enableButtonOk(false);
  ui->contentTable->clearContents();
  ui->contentTable->setRowCount(0);
  pList.clear();

  rNumber       = trModel->record(index.row()).value("id").toULongLong();
  trNumber      = trModel->record(index.row()).value("transaction_id").toULongLong();
  rPayment      = trModel->record(index.row()).value("payment").toDouble();
  rProfit       = trModel->record(index.row()).value("profit").toDouble();
  item_discounts= trModel->record(index.row()).value("item_discounts").toString();
  qDebug()<<"==> Selected Reservation number:"<<rNumber<<" Transaction #"<< trNumber;
  Azahar *myDb = new Azahar;
  myDb->setDatabase(db);
  TransactionInfo tInfo = myDb->getTransactionInfo(trNumber);
  clientId = tInfo.clientid;
  trDate   = tInfo.date;
  QStringList _pList = tInfo.itemlist.split(",");
  int count = 0;
  //Iterate each product/group
  foreach(QString str, _pList) {
    qulonglong code = str.section('/',0,0).toULongLong();
    double     qty  = str.section('/',1,1).toDouble();
    if (code <= 0 ) break;
    count++;
    ProductInfo pInfo = myDb->getProductInfo(QString::number(code));
    pInfo.qtyOnList = qty;
    pList << pInfo;
    //insert to the cntent table
    int rowCount = ui->contentTable->rowCount();
    ui->contentTable->insertRow(rowCount);
    ui->contentTable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(qty)));
    ui->contentTable->setItem(rowCount, 1, new QTableWidgetItem(pInfo.desc));
  }