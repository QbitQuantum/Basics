void RDCutDialog::RefreshCarts()
{
  QString sql;
  RDSqlQuery *q;
  RDListViewItem *l;
  QString group=cut_group_box->currentText();

  if(!cut_cutname->isEmpty()) {
  }
  cut_cart_list->clear();
  if(group==QString(tr("ALL"))) {
    group="";
  }
  QString schedcode="";
  if(cut_schedcode_box->currentText()!=tr("ALL")) {
    schedcode=cut_schedcode_box->currentText();
  }
  sql=QString().sprintf("select CART.NUMBER,CART.TITLE,CART.GROUP_NAME,\
                         GROUPS.COLOR,CART.TYPE from CART left join GROUPS \
                         on CART.GROUP_NAME=GROUPS.NAME \
                         %s&&(CART.TYPE=%u)",
			(const char *)RDCartSearchText(cut_filter_edit->text(),
						       group,schedcode.utf8(),
						       false),
			RDCart::Audio);
  if(cut_exclude_tracks) {
    sql+="&&(CART.OWNER is null)";
  }
  if(cart_limit_box->isChecked()) {
    sql+=QString().sprintf(" limit %d",RD_LIMITED_CART_SEARCH_QUANTITY);
  }
  q=new RDSqlQuery(sql);
  int step=0;
  int count=0;
  cut_progress_dialog->setTotalSteps(q->size()/RDCUT_DIALOG_STEP_SIZE);
  cut_progress_dialog->setProgress(0);
  while(q->next()) {
    l=new RDListViewItem(cut_cart_list);
    switch((RDCart::Type)q->value(4).toUInt()) {
    case RDCart::Audio:
      l->setPixmap(0,*cut_playout_map);
      break;

    case RDCart::All:
    case RDCart::Macro:
      break;
    }
    l->setText(1,QString().sprintf("%06u",q->value(0).toUInt()));   // Number

    l->setText(2,q->value(1).toString());     // Title
    l->setText(3,q->value(2).toString());     // Group
    l->setTextColor(3,q->value(3).toString(),QFont::Bold);
    if(count++>RDCUT_DIALOG_STEP_SIZE) {
      cut_progress_dialog->setProgress(++step);
      count=0;
      qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
  }
  cut_progress_dialog->reset();
  delete q;
  cut_search_button->setDisabled(true);
}