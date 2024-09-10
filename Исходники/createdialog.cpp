HgCreateDialog::HgCreateDialog(const QString &directory, QWidget *parent):
    KDialog(parent, Qt::Dialog),
    m_workingDirectory(directory)
{
    // dialog properties
    this->setCaption(i18nc("@title:window", 
                "<application>Hg</application> Initialize Repository"));
    this->setButtons(KDialog::Ok | KDialog::Cancel);
    this->setDefaultButton(KDialog::Ok);
    this->setButtonText(KDialog::Ok, i18nc("@action:button", "Initialize Repository"));
    //this->enableButtonOk(false);


    //////////////
    // Setup UI //
    //////////////
    
    m_directory = new QLabel("<b>" + m_workingDirectory + "</b>");
    m_repoNameEdit = new KLineEdit;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_directory);
    mainLayout->addWidget(m_repoNameEdit);

    QFrame *frame = new QFrame;
    frame->setLayout(mainLayout);
    setMainWidget(frame);
    m_repoNameEdit->setFocus();
}