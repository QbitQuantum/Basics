NewBranchDialog::NewBranchDialog(QWidget *parent):
    KDialog(parent, Qt::Dialog)
{
    // dialog properties
    this->setCaption(i18nc("@title:window", 
                "<application>Hg</application> Commit: New Branch"));
    this->setButtons(KDialog::Ok | KDialog::Cancel);
    this->setDefaultButton(KDialog::Ok);
    this->enableButtonOk(false); // since commit message is empty when loaded

    m_branchList = HgWrapper::instance()->getBranches();

    QLabel *message = new QLabel(i18nc("@label", "Enter new branch name"));
    m_branchNameInput = new KLineEdit;
    m_errorLabel = new QLabel;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(message);
    layout->addWidget(m_branchNameInput);
    layout->addWidget(m_errorLabel);

    QFrame *frame = new QFrame;
    frame->setLayout(layout);
    setMainWidget(frame);

    connect(m_branchNameInput, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotTextChanged(const QString&)));
}