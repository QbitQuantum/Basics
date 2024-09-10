void RDCartDialog::RefreshCarts()
{
  QString sql;
  RDSqlQuery *q;
  RDListViewItem *l;

  cart_cart_list->clear();
  QString group=cart_group_box->currentText();
  if(group==QString(tr("ALL"))) {
    group="";
  }
  QString schedcode=cart_schedcode_box->currentText();
  if(group==QString(tr("ALL"))) {
    schedcode="";
  }
  if(cart_type==RDCart::All) {
    sql=QString("select ")+
      "CART.NUMBER,"+          // 00
      "CART.TITLE,"+           // 01
      "CART.ARTIST,"+          // 02
      "CART.CLIENT,"+          // 03
      "CART.AGENCY,"+          // 04
      "CART.USER_DEFINED,"+    // 05
      "CART.COMPOSER,"+        // 06
      "CART.CONDUCTOR,"+       // 07
      "CART.START_DATETIME,"+  // 08
      "CART.END_DATETIME,"+    // 09
      "CART.TYPE,"+            // 10
      "CART.FORCED_LENGTH,"+   // 11
      "CART.GROUP_NAME,"+      // 12
      "GROUPS.COLOR "+         // 13
      "from CART left join GROUPS "+
      "on CART.GROUP_NAME=GROUPS.NAME where "+
      GetSearchFilter(cart_filter_edit->text(),group,schedcode);
  }
  else {
    sql=QString("select ")+
      "CART.NUMBER,"+          // 00
      "CART.TITLE,"+           // 01
      "CART.ARTIST,"+          // 02
      "CART.CLIENT,"+          // 03
      "CART.AGENCY,"+          // 04
      "CART.USER_DEFINED,"+    // 05
      "CART.COMPOSER,"+        // 06
      "CART.CONDUCTOR,"+       // 07
      "CART.START_DATETIME,"+  // 08
      "CART.END_DATETIME,"+    // 09
      "CART.TYPE,"+            // 10
      "CART.FORCED_LENGTH,"+   // 11
      "CART.GROUP_NAME,"+      // 12
      "GROUPS.COLOR "+         // 13
      "from CART left join GROUPS "+
      "on CART.GROUP_NAME=GROUPS.NAME where "+
      "("+GetSearchFilter(cart_filter_edit->text(),group,schedcode)+")&&"+
      QString().sprintf("(TYPE=%d)",cart_type);
  }
  if(cart_limit_box->isChecked()) {
    sql+=QString().sprintf(" limit %d",RD_LIMITED_CART_SEARCH_QUANTITY);
  }
  q=new RDSqlQuery(sql);
  int step=0;
  int count=0;
  cart_progress_dialog->setTotalSteps(q->size()/RDCART_DIALOG_STEP_SIZE);
  cart_progress_dialog->setProgress(0);
  while(q->next()) {
    l=new RDListViewItem(cart_cart_list);
    l->setId(q->value(10).toUInt());
    switch((RDCart::Type)q->value(10).toUInt()) {
	case RDCart::Audio:
	  l->setPixmap(0,*cart_playout_map);
	  break;

	case RDCart::Macro:
	  l->setPixmap(0,*cart_macro_map);
	  break;

	default:
	  break;
    }
    l->setText(1,QString().sprintf("%06d",q->value(0).toUInt())); // Number
    l->setText(2,RDGetTimeLength(q->value(11).toInt(),false,true)); // Length
    l->setText(3,q->value(1).toString());                       // Title
    l->setText(4,q->value(2).toString());                       // Artist
    l->setText(5,q->value(12).toString());                      // Group
    l->setText(6,q->value(6).toString());                      // Composer
    l->setText(7,q->value(7).toString());                      // Conductor
    l->setTextColor(5,q->value(13).toString(),QFont::Bold);
    l->setText(8,q->value(3).toString());                       // Client
    l->setText(9,q->value(4).toString());                       // Agency
    l->setText(10,q->value(5).toString());                       // User Defined
    if(!q->value(8).toDate().isNull()) {
      l->setText(11,q->value(8).toDate().toString("MM/dd/yyyy"));  // Start Date
    }
    if(!q->value(10).toDate().isNull()) {
      l->setText(12,q->value(9).toDate().toString("MM/dd/yyyy"));  // End Date
    }
    else {
      l->setText(12,"TFN");
    }
    if(count++>RDCART_DIALOG_STEP_SIZE) {
      cart_progress_dialog->setProgress(++step);
      count=0;
      qApp->processEvents(QEventLoop::ExcludeUserInput);
    }
  }
  cart_progress_dialog->reset();
  delete q;
  cart_search_button->setDisabled(true);
}