void KOnlineBankingSetupWizard::newPage(int id)
{
  QWidget* focus = 0;

  bool ok = true;
  if ((id - d->m_prevPage) == 1) { // one page forward?
    switch (d->m_prevPage) {
      case 0:
        ok = finishFiPage();
        // open the KDE wallet if not already opened
        if (ok && !d->m_wallet) {
          d->m_wallet = Wallet::openWallet(Wallet::NetworkWallet(), winId(), Wallet::Asynchronous);
          connect(d->m_wallet, SIGNAL(walletOpened(bool)), SLOT(walletOpened(bool)));
        }
        focus = m_editUsername;
        break;
      case 1:
        ok = finishLoginPage();
        focus = m_listAccount;
        break;
      case 2:
        m_fDone = ok = finishAccountPage();
        break;
    }

    if (ok) {
      if (focus) {
        focus->setFocus();
      }
    } else {
      // force to go back to prev page
      back();
    }
  } else {