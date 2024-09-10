// BFB: New spinboxPrice. We need to obtain product price, and then calculate offer price
void PromoEditor::productChanged()
{
  qulonglong code = getSelectedProductCode();
  if (code != 0){
    Azahar *myDb = new Azahar;
    myDb->setDatabase(db);
    ProductInfo info = myDb->getProductInfo(QString::number(code));
    ui->spinboxPrice->setValue(info.price*(100.0-ui->spinboxDiscount->value())/100);
  }
  checkValid();
}