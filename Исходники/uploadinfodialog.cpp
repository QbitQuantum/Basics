UploadInfoDialog::UploadInfoDialog(QString infoString)
{

    setWindowIcon( QIcon(":/images/hi64-app-qmoorie.png") );
    setWindowTitle(qApp->applicationName()  + " " + qApp->applicationVersion() + tr(" - Informacje"));

    info = new QLabel(infoString);
    info->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);

    Hashcode = new QTextEdit();
    QPushButton *okButton = new QPushButton(tr("OK"));
    QPushButton *cancelButton = new QPushButton(tr("Anuluj"));
    okButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout -> addWidget(okButton);

    QVBoxLayout *main = new QVBoxLayout;
    main -> addWidget(info);
    main -> addSpacing(10);
    main -> addLayout(buttonLayout);
    setLayout(main);

    okButton->setFocus();

    connect( okButton, SIGNAL(clicked()), this, SLOT(close()));

    getHashInfo();
}