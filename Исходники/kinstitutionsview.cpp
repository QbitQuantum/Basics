void KInstitutionsView::show(void)
{
  if(m_needReload) {
    loadAccounts();
    m_needReload = false;
  }

  // don't forget base class implementation
  KInstitutionsViewDecl::show();

  // if we have a selected account, let the application know about it
  KMyMoneyAccountTreeBaseItem *item = m_accountTree->selectedItem();
  if(item) {
    emit selectObject(item->itemObject());
  }
}