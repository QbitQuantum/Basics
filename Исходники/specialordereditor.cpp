void SpecialOrderEditor::addItem()
{
  double dqty = 1; //if not any value, default is ONE
  QStringList msgP;
  QStringList msgU;
  int incTime = 0;
  Azahar *myDb = new Azahar;
  myDb->setDatabase(db);
  
  if (!ui->editAddQty->text().isEmpty()) {
    dqty = ui->editAddQty->text().toDouble();
  }
  //get selected items from source view
  QItemSelectionModel *selectionModel = ui->sourcePView->selectionModel();
  QModelIndexList indexList = selectionModel->selectedRows(); // pasar el indice que quiera (0=code, 1=name)
  foreach(QModelIndex index, indexList) {
    qulonglong code    = index.data().toULongLong();
    QString    codeStr = index.data().toString();
    bool exists = false;
    ProductInfo pInfo;
    //get product info from hash or db
    if (groupInfo.productsList.contains(code)) {
      pInfo = groupInfo.productsList.take(code);
      //check measures for the product
      if (pInfo.units == 1 ) { //by pieces
        QString tmpStr = ui->editAddQty->text();
        if (tmpStr.endsWith(".00")) tmpStr.chop(3); //discard .00's
        if (tmpStr.endsWith(".0")) tmpStr.chop(2);//discard .00's
        if (tmpStr.contains(".") || tmpStr.contains(",")) {
          int tmp = dqty;
          dqty = tmp; //pass to integer instead of double
          msgP.append(i18n("<i>%1</i> rounded to %2",pInfo.desc,tmp));
          incTime += 1000;
        }
      }
      if (pInfo.stockqty >= pInfo.qtyOnList+dqty)
        pInfo.qtyOnList += dqty; //increment it
      else {
        incTime += 1000;
        msgU.append(i18n("<i>%1</i> <b>requested %2, on stock %3</b><br>", pInfo.desc,dqty,pInfo.stockqty));
      }
      //if not enough, its not incremented.
      exists = true;
    } else {
      pInfo = myDb->getProductInfo(codeStr);
      //check measures for the product
      if (pInfo.units == 1) { //by pieces
        QString tmpStr = ui->editAddQty->text();
        if (tmpStr.endsWith(".00")) tmpStr.chop(3);//discard .00's
        if (tmpStr.endsWith(".0")) tmpStr.chop(2);//discard .00's
        if (tmpStr.contains(".") || tmpStr.contains(",")) {
          int tmp = dqty;
          dqty = tmp; //pass to integer instead of double
          msgP.append(i18n("<i>%1</i> rounded to %2",pInfo.desc,tmp));
          incTime += 1000;
        }
      }
      pInfo.qtyOnList = 0;
      if (pInfo.stockqty >= dqty)
        pInfo.qtyOnList = dqty;
      else {
        incTime += 1000;
        msgU.append(i18n("<i>%1</i> <b>requested %2, on stock %3</b><br>", pInfo.desc,dqty,pInfo.stockqty));
      }
    }

    // Insert/Update GroupView
    if (!exists) {
      //check if it is available.
      if (pInfo.qtyOnList <= 0 ) {
        //NO, its not available.
        continue;
        qDebug()<<"Continue...";
      }
      // Insert into the groupView
      int rowCount = ui->groupView->rowCount();
      ui->groupView->insertRow(rowCount);
      ui->groupView->setItem(rowCount, 0, new QTableWidgetItem(QString::number(dqty)));
      ui->groupView->setItem(rowCount, 1, new QTableWidgetItem(pInfo.desc));
    } else {
      if (pInfo.qtyOnList <= 0 ) {
        //NO, its not available.
        continue;
        qDebug()<<"Continue...";
      }
      //simply update the groupView with the new qty
      for (int ri=0; ri<ui->groupView->rowCount(); ++ri)
      {
        QTableWidgetItem * item = ui->groupView->item(ri, 1);
        QString name = item->data(Qt::DisplayRole).toString();
        if (name == pInfo.desc) {
          //update
          QTableWidgetItem *itemQ = ui->groupView->item(ri, 0);//item qty
          itemQ->setData(Qt::EditRole, QVariant(pInfo.qtyOnList));
          continue;
        }
      }
    }
    // update info of the group
    groupInfo.count = groupInfo.count+dqty;
    groupInfo.cost  += pInfo.cost*dqty;  //pInfo.qtyOnList;
    groupInfo.price += pInfo.price*dqty; //pInfo.qtyOnList;
    //NOTE:group price is not affected by any product discount, it takes normal price.
    //     Discounts are taken into consideration after adding to the purchase list, when calculating taxes and price for the SO.
    bool yes = false;
    if (pInfo.stockqty >= dqty )
      yes = true;
    groupInfo.isAvailable = (groupInfo.isAvailable && yes );
    // Insert product to the group hash
    groupInfo.productsList.insert(code, pInfo);
    if (!yes) {
      //Just warning!... the insert into the view is above...
      qDebug()<<"Product is not available!";
    }
  }