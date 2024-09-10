int main(int argc,char *argv[])
{
    if (argc < 1)
        return 1;
    const QString skinFile = QString::fromUtf8(argv[1]);
    QApplication app(argc,argv);
    QMainWindow mw;

    DeviceSkinParameters params;
    QString errorMessage;
    if (!params.read(skinFile, DeviceSkinParameters::ReadAll, &errorMessage)) {
	qWarning() << errorMessage;
	return 1;
    }
    DeviceSkin ds(params, &mw);
    // View Dialog
    QDialog *dialog = new QDialog();
    QHBoxLayout *dialogLayout = new QHBoxLayout();
    dialog->setLayout(dialogLayout);
    QDialogButtonBox *dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    QObject::connect(dialogButtonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    QObject::connect(dialogButtonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    dialogLayout->addWidget(dialogButtonBox);
    dialog->setFixedSize(params.screenSize());
    dialog->setParent(&ds, Qt::SubWindow);
    dialog->setAutoFillBackground(true);
    ds.setView(dialog);

    QObject::connect(&ds, SIGNAL(popupMenu()), &mw, SLOT(close()));
    QObject::connect(&ds, SIGNAL(skinKeyPressEvent(int,QString,bool)), &mw, SLOT(close()));
    mw.show();
    return app.exec();
}