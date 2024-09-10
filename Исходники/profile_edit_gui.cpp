void ProfileEditGui::buttonOk()
{
    QString strPassword = ui.lineEdit_password->text();

    // empty
    if (strPassword.isEmpty())
    {
        QMessageBox::critical(0, QString::null, tr("Password is empty!"));
        return;
    }

    // encrypt pass
    SimpleCrypt *pSimpleCrypt = new SimpleCrypt();
    strPassword = pSimpleCrypt->encrypt(strNick, strPassword);
    delete pSimpleCrypt;

    Config *pConfig = new Config(ProfileConfig, strNick);
    pConfig->set("pass", strPassword);
    delete pConfig;

    // current nick
    QString strMe = Settings::instance()->get("nick");
    if (strNick == strMe)
        Settings::instance()->set("pass", strPassword);

    // close
    this->close();
}