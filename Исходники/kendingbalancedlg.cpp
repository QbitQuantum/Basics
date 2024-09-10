void KEndingBalanceDlg::accept()
{
  if ((!field("interestEditValid").toBool() || createTransaction(d->m_tInterest, -1, field("interestEdit").value<MyMoneyMoney>(), field("interestCategoryEdit").toString(), field("interestDateEdit").toDate()))
      && (!field("chargesEditValid").toBool() || createTransaction(d->m_tCharges, 1, field("chargesEdit").value<MyMoneyMoney>(), field("chargesCategoryEdit").toString(), field("chargesDateEdit").toDate())))
    KEndingBalanceDlgDecl::accept();
}