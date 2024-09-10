void PurchaseEditor::addItemToList()
{
  ProductInfo pInfo;
  Azahar *myDb = new Azahar;
  myDb->setDatabase(db);
  bool ok=false;

  if (ui->editCode->text().isEmpty()) ui->editCode->setFocus();
  else if (ui->editDesc->text().isEmpty()) ui->editDesc->setFocus();
  else if (ui->editPoints->text().isEmpty()) ui->editPoints->setFocus();
  else if (ui->editCost->text().isEmpty()) ui->editCost->setFocus();
  else if (ui->editTax->text().isEmpty()) ui->editTax->setFocus();
  else if (ui->editFinalPrice->text().isEmpty()) ui->editFinalPrice->setFocus();
  else if (ui->editQty->text().isEmpty() || ui->editQty->text()=="0") ui->editQty->setFocus();
  else if ((ui->editUtility->text().isEmpty() && ui->editFinalPrice->text().isEmpty()) || ui->editFinalPrice->text().toDouble()<=ui->editCost->text().toDouble() ) ui->editFinalPrice->setFocus();
  else if (ui->groupBoxedItem->isChecked() && (ui->editItemsPerBox->text().isEmpty() || ui->editItemsPerBox->text()=="0"))  ui->editItemsPerBox->setFocus();
  else if (ui->groupBoxedItem->isChecked() && (ui->editPricePerBox->text().isEmpty() || ui->editPricePerBox->text()=="0")) ui->editPricePerBox->setFocus();
  else ok = true;

  if (ok) {
    ProductInfo info = myDb->getProductInfo(QString::number(getCode()));
    if (info.code == 0) {
      info.code = getCode();
      info.lastProviderId=1; //for now.. fixme in the future
    }
    //update p.info from the dialog
    info.desc    = getDescription();
    info.price   = getPrice();
    info.cost    = getCost();
    info.tax     = getTax1();
    //FIXME: add tax models
    //info.extratax= getTax2();
    info.photo   = getPhotoBA();
    info.units   = getMeasureId();
    info.category= getCategoryId();
    info.profit  = getProfit();
    info.points  = getPoints();
    info.stockqty= getQtyOnDb();
    info.purchaseQty = getPurchaseQty();
    double finalCount = info.purchaseQty + info.stockqty; // WHAT FOR??
    info.validDiscount = productExists; //used to check if product is already on db.
    //FIXME: NEXT 2 lines are temporal remove on 0.8 version
    //info.alphaCode = "-NA-";
    //FIXME: last providerId for an existent must be gotten from db since we dont have that field here. Provide a combobox to select one and a button to add a new one.
    //info.lastProviderId = 1;

    if (info.isAGroup) {
      // get each product fo the group/pack
      QStringList list = gelem.split(",");
      for (int i=0; i<list.count(); ++i) {
        QStringList tmp = list.at(i).split("/");
        if (tmp.count() == 2) { //ok 2 fields
          qulonglong  code  = tmp.at(0).toULongLong();
          pInfo = myDb->getProductInfo(QString::number(code));
          pInfo.purchaseQty = getPurchaseQty();
          pInfo.validDiscount = true; // all grouped products exists
          insertProduct(pInfo); ///inserting each product of the group
        } // correct fields
      }//for each element
    } else insertProduct(info);

    resetEdits();
    ui->editCode->setFocus();
  }
}