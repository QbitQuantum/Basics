double donationDialog::EUR2BTC()
{
	QNetworkReply *rep = ((MainWindow*)parent())->mgr->get(QNetworkRequest(QUrl("https://blockchain.info/de/tobtc?currency=EUR&value=1")));
	QByteArray raw;

	rep->ignoreSslErrors();

	lineEdit_payment2->setText(tr("getting current exchange rate..."));
	comboBox->setEnabled(false);
	horizontalSlider->setEnabled(false);
	pushButton->setEnabled(false);

	((MainWindow*)parent())->timeout.start();

	while(rep->isRunning())
	{
		QCoreApplication::processEvents();

		if(((MainWindow*)parent())->timeout.hasExpired(3000))
		{
			rep->abort();
		}
	}

	comboBox->setEnabled(true);
	horizontalSlider->setEnabled(true);
	pushButton->setEnabled(true);

	if(rep->error())
	{
		QMessageBox::warning(this, APPNAME, tr("Current exchange rate could not be determined!\n\nPlease specify the desired amount manually..."));

		return 0.0;
	}

	raw = rep->readAll();

	rep->deleteLater();

	return raw.toDouble();
}