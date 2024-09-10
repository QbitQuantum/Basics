int DMessageBox::showContinueCancelWidget(QMessageBox::Icon icon,
                                          QWidget* const parent,
                                          const QString& caption,
                                          const QString& text,
                                          QWidget* const listWidget,
                                          const QString& dontAskAgainName)
{
    if (!readMsgBoxShouldBeShown(dontAskAgainName))
    {
        return QMessageBox::Yes;
    }

    QDialog* const dialog = new QDialog(parent, Qt::Dialog);
    dialog->setWindowTitle(caption);
    dialog->setObjectName(QLatin1String("showContinueCancel"));
    dialog->setModal(true);

    QDialogButtonBox* const buttons = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::Cancel, dialog);
    buttons->button(QDialogButtonBox::Yes)->setDefault(true);
    buttons->button(QDialogButtonBox::Yes)->setText(i18n("Continue"));
    buttons->button(QDialogButtonBox::Cancel)->setShortcut(Qt::Key_Escape);

    QObject::connect(buttons->button(QDialogButtonBox::Yes), SIGNAL(clicked()),
                     dialog, SLOT(accept()));

    QObject::connect(buttons->button(QDialogButtonBox::Cancel), SIGNAL(clicked()),
                     dialog, SLOT(reject()));

    bool checkboxResult = false;
    const int result    = createMessageBox(dialog, buttons, createIcon(icon), text, listWidget,
                                           dontAskAgainName.isEmpty() ? QString() : i18n("Do not ask again"),
                                           &checkboxResult);

    if (result != QDialog::Accepted)
    {
        return QMessageBox::Cancel;
    }

    saveMsgBoxShouldBeShown(dontAskAgainName, checkboxResult);

    return QMessageBox::Yes;
}