CompositeKey DatabaseOpenWidget::databaseKey()
{
    CompositeKey masterKey;

    if (m_ui->checkPassword->isChecked()) {
        masterKey.addKey(PasswordKey(m_ui->editPassword->text()));
    }

    QHash<QString, QVariant> lastKeyFiles = config()->get("LastKeyFiles").toHash();

    if (m_ui->checkKeyFile->isChecked()) {
        FileKey key;
        QString keyFilename = m_ui->comboKeyFile->currentText();
        QString errorMsg;
        if (!key.load(keyFilename, &errorMsg)) {
            MessageBox::warning(this, tr("Error"), tr("Can't open key file").append(":\n").append(errorMsg));
            return CompositeKey();
        }
        masterKey.addKey(key);
        lastKeyFiles[m_filename] = keyFilename;
    }
    else {
        lastKeyFiles.remove(m_filename);
    }

    if (config()->get("RememberLastKeyFiles").toBool()) {
        config()->set("LastKeyFiles", lastKeyFiles);
    }

    return masterKey;
}