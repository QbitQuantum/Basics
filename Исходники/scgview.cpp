void SCgView::changeIdentifier()
{
    Q_ASSERT(mContextObject);

    QDialog dialog(this);
    dialog.setWindowTitle(tr("Change identifier"));

    QLabel* label = new QLabel(tr("New identifier:"),&dialog);
    QLineEdit* lineEdit = new QLineEdit(&dialog);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);
    buttonBox->setParent(&dialog);

    connect(buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(buttonBox);

    QCompleter *completer = new QCompleter(static_cast<SCgScene*>(scene())->idtfList(), &dialog);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    lineEdit->setCompleter(completer);
    QString oldIdtf = mContextObject->idtfValue();

    lineEdit->setText(oldIdtf);
    lineEdit->selectAll();

    dialog.setLayout(layout);
    lineEdit->setFocus();

    if (dialog.exec())
    {
        QString newIdtf = lineEdit->text();
        if(oldIdtf != newIdtf)
            static_cast<SCgScene*>(scene())->changeIdtfCommand(mContextObject, newIdtf);
    }
}