void JBlockerMainWindow::slt_loadingStart()
{
    this->statusBar()->showMessage(tr("LOADING MESSAGES ..."));
    // QMessageBox::information(this, QString(), QString("PROGRAM NEED TO LOAD MESSAGES"), QMessageBox::Ok);
    /* Create dialog */
    QDialog dialog;
    dialog.setWindowTitle(tr("Account Selection"));
    QHBoxLayout* layout = new QHBoxLayout();
    /* Label for dialog */
    QLabel* dialogLabel = new QLabel(tr("Select An Account:"));
    layout->addWidget(dialogLabel, 0, Qt::AlignHCenter);
    /* Combo box for selecting account */
    QComboBox* accountComboBox = new QComboBox();
    accountComboBox->setFixedWidth(280);
    /* Get account name list from message core */
    accountComboBox->addItems(p_messageCore->getAccountNameList());
    layout->addWidget(accountComboBox, 0, Qt::AlignHCenter);
    /* Button for dialog */
    QPushButton* dialogButton = new QPushButton(tr("Confirm"));
    layout->addWidget(dialogButton, 0, Qt::AlignHCenter);
    dialog.setLayout(layout);
    QObject::connect(dialogButton, SIGNAL(clicked()), &dialog, SLOT(accept()));
    dialog.exec();
    if(dialog.result())
    {
        /* Set selected account id */
        p_messageCore->setSelectedAccountId(accountComboBox->currentIndex());
    }

    this->statusBar()->addPermanentWidget(p_progressBar, 0);
    p_progressBar->setValue(0);
    p_progressBar->show();
    /* Core runs */
    p_messageCore->run();
}