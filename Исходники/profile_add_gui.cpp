void ProfileAddGui::buttonOk()
{
    QString strNick = ui.lineEdit_nick->text().trimmed();
    QString strPassword = ui.lineEdit_password->text();

    // empty
    if (strNick.isEmpty())
    {
        QMessageBox::critical(0, QString::null, tr("Nick is empty!"));
        return;
    }

    // check nick
    QString strPass;
    if (ui.radioButton_unregistered_nick->isChecked())
    {
        // fix nick
        if (strNick.at(0) != '~')
            strNick = "~"+strNick;

        strPass = QString::null;
    }
    else if (ui.radioButton_registered_nick->isChecked())
    {
        // fix nick
        if (strNick.at(0) == '~')
            strNick.remove(0,1);

        strPass = ui.lineEdit_password->text();
    }

    // fix nick
    if ((strPass.isEmpty()) && (strNick.at(0) != '~'))
        strNick = '~'+strNick;

    // fix too long nick
    if ((strPass.isEmpty()) && (strNick.size() > 32))
        strNick = strNick.left(32);

    // exist profile
    if (profileManager->existProfile(strNick))
    {
        QMessageBox::critical(0, QString::null, tr("Profile already exists!"));
        return;
    }

    // encrypt pass
    if (!strPass.isEmpty())
    {
        SimpleCrypt *pSimpleCrypt = new SimpleCrypt();
        strPassword = pSimpleCrypt->encrypt(strNick, strPassword);
        delete pSimpleCrypt;
    }

    // save
    Config *pConfig = new Config(ProfileConfig, strNick);
    pConfig->set("nick", strNick);
    pConfig->set("pass", strPassword);
    delete pConfig;

    // refresh
    profileManager->refreshAllLists();

    // close
    this->close();
}