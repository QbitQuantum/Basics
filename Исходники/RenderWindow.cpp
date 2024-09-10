void RenderWindow::sAdd()
{
  bool ok = false;
  bool active = false;

  QString name;
  QString varType;
  QVariant var;

  NewVariant newVar(this);

  while(!ok)
  {
    if(newVar.exec() != QDialog::Accepted)
      return;

    name = newVar._name->text();
    varType = newVar._type->currentText();

    ok = !_params.contains(name);
    if(!ok)
      QMessageBox::warning(this, tr("Name already exists"), tr("The name for the parameter you specified already exists in the list."));
  }


  BoolEdit * be = 0;
  IntEdit * ie = 0;
  DoubleEdit * de = 0;
  StringEdit * se = 0;
  ListEdit * le = 0;

  if(varType == NewVariant::tr("String")) {
    se = new StringEdit(this);
    se->_name->setText(name);
    ok = (se->exec() == QDialog::Accepted);
    var = QVariant(se->_value->text());
    active = se->_active->isChecked();
    delete se;
    se = 0;
  } else if(varType == NewVariant::tr("Int")) {
    ie = new IntEdit(this);
    ie->_name->setText(name);
    ok = (ie->exec() == QDialog::Accepted);
    var = QVariant(ie->_value->text().toInt());
    active = ie->_active->isChecked();
    delete ie;
    ie = 0;
  } else if(varType == NewVariant::tr("Double")) {
    de = new DoubleEdit(this);
    de->_name->setText(name);
    ok = (de->exec() == QDialog::Accepted);
    var = QVariant(de->_value->text().toDouble());
    active = de->_active->isChecked();
    delete de;
    de = 0;
  } else if(varType == NewVariant::tr("Bool")) {
    be = new BoolEdit(this);
    be->_name->setText(name);
    ok = (be->exec() == QDialog::Accepted);
    var = QVariant((bool)be->value());
    active = be->_active->isChecked();
    delete be;
    be = 0;
  } else if(varType == NewVariant::tr("List")) {
    le = new ListEdit(this);
    le->_name->setText(name);
    ok = (le->exec() == QDialog::Accepted);
    var = QVariant(le->list());
    active = le->_active->isChecked();
    delete le;
    le = 0;
  } else {
    QMessageBox::warning(this, tr("Unknown Type"), QString(tr("I do not understand the type %1.")).arg(varType));
    return;
  }

  if(!ok)
    return;

  _params[name] = var;

  int r = _table->rowCount();
  _table->setRowCount(r+1);
  QTableWidgetItem * ctItem = new QTableWidgetItem();
  ctItem->setFlags(Qt::ItemIsUserCheckable);
  ctItem->setCheckState((active ? Qt::Checked : Qt::Unchecked));
  _table->setItem(r, 0, ctItem);
  _table->setItem(r, 1, new QTableWidgetItem(name));
  _table->setItem(r, 2, new QTableWidgetItem(var.typeName()));
  _table->setItem(r, 3, new QTableWidgetItem(var.toString()));
  sSelectionChanged();
}