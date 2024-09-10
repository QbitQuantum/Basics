void KNewFileMenuPrivate::executeRealFileOrDir(const KNewFileMenuSingleton::Entry& entry)
{
    // The template is not a desktop file
    // Show the small dialog for getting the destination filename
    QString text = entry.text;
    text.remove("..."); // the ... is fine for the menu item but not for the default filename
    text = text.trimmed(); // In some languages, there is a space in front of "...", see bug 268895
    m_strategy.m_src = entry.templatePath;

    KUrl defaultFile(m_popupFiles.first());
    defaultFile.addPath(KIO::encodeFileName(text));
    if (defaultFile.isLocalFile() && QFile::exists(defaultFile.toLocalFile()))
        text = KIO::RenameDialog::suggestName(m_popupFiles.first(), text);
    
    KDialog* fileDialog = new KDialog(m_parentWidget);
    fileDialog->setAttribute(Qt::WA_DeleteOnClose);
    fileDialog->setModal(q->isModal());
    fileDialog->setButtons(KDialog::Ok | KDialog::Cancel);
    
    QWidget* mainWidget = new QWidget(fileDialog);
    QVBoxLayout *layout = new QVBoxLayout(mainWidget);
    QLabel *label = new QLabel(entry.comment);

    // We don't set the text of lineEdit in its constructor because the clear button would not be shown then.
    // It seems that setClearButtonShown(true) must be called *before* the text is set to make it work.
    // TODO: should probably be investigated and fixed in KLineEdit.
    KLineEdit *lineEdit = new KLineEdit;
    lineEdit->setClearButtonShown(true);
    lineEdit->setText(text);

    _k_slotTextChanged(text);
    QObject::connect(lineEdit, SIGNAL(textChanged(const QString &)), q, SLOT(_k_slotTextChanged(const QString &)));
    
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    
    fileDialog->setMainWidget(mainWidget);
    QObject::connect(fileDialog, SIGNAL(accepted()), q, SLOT(_k_slotRealFileOrDir()));
    QObject::connect(fileDialog, SIGNAL(rejected()), q, SLOT(_k_slotAbortDialog()));
 
    fileDialog->show();
    lineEdit->selectAll();
    lineEdit->setFocus();
}