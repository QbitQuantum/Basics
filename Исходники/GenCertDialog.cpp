void GenCertDialog::genPerson()
{
	/* Check the data from the GUI. */
	std::string genLoc  = ui.node_input->text().toUtf8().constData();
	RsPgpId PGPId;
	bool isHiddenLoc = false;

    if (ui.hidden_checkbox->isChecked())
	{
		std::string hl = ui.hiddenaddr_input->text().toStdString();
		uint16_t port  = ui.hiddenport_spinBox->value();
		if (!RsInit::SetHiddenLocation(hl, port))	/* parses it */
		{
			/* Message Dialog */
			QMessageBox::warning(this,
				tr("Invalid hidden node"),
			tr("Please enter a valid address of the form: 31769173498.onion:7800 or [52 characters].b32.i2p"),
			QMessageBox::Ok);
			return;
		}
		isHiddenLoc = true;
	}

	if (!genNewGPGKey) {
		if (genLoc.length() < 3) {
			/* Message Dialog */
			QMessageBox::warning(this,
								 tr("PGP key pair generation failure"),
								 tr("Node field is required with a minimum of 3 characters"),
								 QMessageBox::Ok);
			return;
		}
		int pgpidx = ui.genPGPuser->currentIndex();
		if (pgpidx < 0)
		{
			/* Message Dialog */
			QMessageBox::warning(this,
								 tr("Profile generation failure"),
								 tr("Missing PGP certificate"),
								 QMessageBox::Ok);
			return;
		}
		QVariant data = ui.genPGPuser->itemData(pgpidx);
		PGPId = RsPgpId((data.toString()).toStdString());
	} else {
		if (ui.password_input->text().length() < 3 || ui.name_input->text().length() < 3 || genLoc.length() < 3) {
			/* Message Dialog */
			QMessageBox::warning(this,
								 tr("PGP key pair generation failure"),
								 tr("All fields are required with a minimum of 3 characters"),
								 QMessageBox::Ok);
			return;
		}

		if(ui.password_input->text() != ui.password_input_2->text())
		{
			QMessageBox::warning(this,
								 tr("PGP key pair generation failure"),
								 tr("Passwords do not match"),
								 QMessageBox::Ok);
			return;
		}
		//generate a new gpg key
		std::string err_string;
		ui.no_gpg_key_label->setText(tr("Generating new PGP key pair, please be patient: this process needs generating large prime numbers, and can take some minutes on slow computers. \n\nFill in your PGP password when asked, to sign your new key."));
		ui.no_gpg_key_label->show();
		ui.new_gpg_key_checkbox->hide();
		ui.name_label->hide();
		ui.name_input->hide();
//		ui.email_label->hide();
//		ui.email_input->hide();
		ui.password_label_2->hide();
		ui.password_input_2->hide();
		ui.password_label->hide();
		ui.password_input->hide();
		ui.genPGPuserlabel->hide();
		ui.genPGPuser->hide();
		ui.node_label->hide();
		ui.node_input->hide();
        ui.genButton2->hide();
		ui.importIdentity_PB->hide();
		ui.genprofileinfo_label->hide();
        ui.hidden_checkbox->hide();
        ui.adv_checkbox->hide();
        ui.keylength_label->hide();
		ui.keylength_comboBox->hide();

		setCursor(Qt::WaitCursor) ;

		QCoreApplication::processEvents();
		while(QAbstractEventDispatcher::instance()->processEvents(QEventLoop::AllEvents)) ;

		std::string email_str = "" ;
		RsAccounts::GeneratePGPCertificate(
					ui.name_input->text().toUtf8().constData(),
					email_str.c_str(),
					ui.password_input->text().toUtf8().constData(),
					PGPId,
					ui.keylength_comboBox->itemData(ui.keylength_comboBox->currentIndex()).toInt(),
					err_string);

		setCursor(Qt::ArrowCursor) ;
	}

	//generate a random ssl password
	std::string sslPasswd = RSRandom::random_alphaNumericString(RsInit::getSslPwdLen()) ;

	/* GenerateSSLCertificate - selects the PGP Account */
	//RsInit::SelectGPGAccount(PGPId);

	RsPeerId sslId;
	std::cerr << "GenCertDialog::genPerson() Generating SSL cert with gpg id : " << PGPId << std::endl;
	std::string err;
	this->hide();//To show dialog asking password PGP Key.
	bool okGen = RsAccounts::GenerateSSLCertificate(PGPId, "", genLoc, "", isHiddenLoc, sslPasswd, sslId, err);

	if (okGen)
	{
		/* complete the process */
		RsInit::LoadPassword(sslPasswd);
		if (Rshare::loadCertificate(sslId, false)) {
			accept();
		}
	}
	else
	{
		/* Message Dialog */
		QMessageBox::warning(this,
                               tr("Profile generation failure"),
                               tr("Failed to generate your new certificate, maybe PGP password is wrong!"),
                               QMessageBox::Ok);
		reject();
       }
}