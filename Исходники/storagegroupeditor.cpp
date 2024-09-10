SGPopupResult StorageGroupPopup::showPopup(MythMainWindow *parent,
                                 QString title, QString message, QString& text)
{
    MythPopupBox *popup = new MythPopupBox(parent, title.toAscii().constData());
    popup->addLabel(message);

    MythLineEdit *textEdit = new MythLineEdit(popup, "chooseEdit");
    textEdit->setText(text);
    popup->addWidget(textEdit);

    popup->addButton(QObject::tr("OK"),     popup, SLOT(accept()));
    popup->addButton(QObject::tr("Cancel"), popup, SLOT(reject()));

    textEdit->setFocus();

    bool ok = (MythDialog::Accepted == popup->ExecPopup());
    if (ok)
    {
        text = textEdit->text();
        text.detach();
    }

    popup->hide();
    popup->deleteLater();

    return (ok) ? SGPopup_OK : SGPopup_CANCEL;
}