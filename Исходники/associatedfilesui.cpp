QString AssociatedFilesUI::associateUrl(const QUrl &url, const QString &entryId, const File *bibTeXfile, QWidget *parent) {
    QPointer<QDialog> dlg = new QDialog(parent);
    QBoxLayout *layout = new QVBoxLayout(dlg);
    QPointer<AssociatedFilesUI> ui = new AssociatedFilesUI(entryId, bibTeXfile, dlg);
    layout->addWidget(ui);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, dlg);
    layout->addWidget(buttonBox);
    dlg->setLayout(layout);

    connect(buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, dlg.data(), &QDialog::accept);
    connect(buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, dlg.data(), &QDialog::reject);

    if (AssociatedFiles::urlIsLocal(url))
        ui->setupForLocalFile(url, entryId);
    else
        ui->setupForRemoteUrl(url, entryId);

    const bool accepted = dlg->exec() == QDialog::Accepted;
    bool success = true;
    QString referenceString;
    if (accepted) {
        const QUrl newUrl = AssociatedFiles::copyDocument(url, entryId, bibTeXfile, ui->renameOperation(), ui->moveCopyOperation(), dlg, ui->userDefinedFilename());
        success &= !newUrl.isEmpty();
        if (success) {
            referenceString = AssociatedFiles::associateDocumentURL(newUrl, bibTeXfile, ui->pathType());
            success &= !referenceString.isEmpty();
        }
    }

    delete dlg;
    return accepted && success ? referenceString : QString();
}