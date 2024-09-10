void HiddenFileView::checkBoxClicked(QCheckBox* chkBox,KToggleAction* action,QLineEdit* edit, int column,QPtrList<QRegExp> & reqExpList,bool b) {
  // We don't save the old state so
  // disable the tristate mode
  chkBox->setTristate(false);
  action->setChecked(b);
  chkBox->setChecked(b);

  HiddenListViewItem* item;
  for (item = static_cast<HiddenListViewItem*>(_dlg->hiddenListView->firstChild());item;
       item = static_cast<HiddenListViewItem*>(item->nextSibling()))
  {
    if (!item->isSelected())
        continue;
        
    if (b == item->isOn(column))
        continue;
            
    if (!b) {
        QRegExp* rx = getRegExpListMatch(item->text(0),reqExpList);
        
        // Perhaps the file was hidden because it started with a dot
        if (!rx && item->text(0)[0]=='.' && _dlg->hideDotFilesChk->isChecked()) {
            int result = KMessageBox::questionYesNo(_dlg,i18n(
                    "<qt>Some files you have selected are hidden because they start with a dot; "
                    "do you want to uncheck all files starting with a dot?</qt>"),i18n("Files Starting With Dot"),i18n("Uncheck Hidden"), i18n("Keep Hidden"));
                
            if (result == KMessageBox::No) {
                QPtrList<HiddenListViewItem> lst = getMatchingItems(QRegExp(".*",false,true));
                deselect(lst);
            } else {
                _dlg->hideDotFilesChk->setChecked(false);
            }
            continue;
        } else {
            if (rx) {
                // perhaps it is matched by a wildcard string
                QString p = rx->pattern();
                if ( p.find("*") > -1 ||
                        p.find("?") > -1 )
                {
                    // TODO after message freeze: why show three times the wildcard string? Once should be enough.
		    // TODO remove <b></b> and use <qt> instead
                    int result = KMessageBox::questionYesNo(_dlg,i18n(
                    "<b></b>Some files you have selected are matched by the wildcarded string <b>'%1'</b>; "
                    "do you want to uncheck all files matching <b>'%1'</b>?").arg(rx->pattern()).arg(rx->pattern()).arg(rx->pattern()),
                    i18n("Wildcarded String"),i18n("Uncheck Matches"),i18n("Keep Selected"));
            
                    QPtrList<HiddenListViewItem> lst = getMatchingItems( *rx );
            
                    if (result == KMessageBox::No) {
                        deselect(lst);
                    } else {
                        setState(lst,column,false);
                        reqExpList.remove(rx);
                        updateEdit(edit, reqExpList);
                    }
                    continue;
                } else {
                    reqExpList.remove(rx);
                    updateEdit(edit, reqExpList);
                }
            }   
        }
    }
    else {
        reqExpList.append( new QRegExp(item->text(0)) );
        updateEdit(edit, reqExpList);
    }
    
    item->setOn(column,b);
  }

  _dlg->hiddenListView->update();
}