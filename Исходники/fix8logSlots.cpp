void Fix8Log::aboutSlot()
{

    QDialog *aboutDialog = new QDialog();
    QVBoxLayout *aboutLayout = new QVBoxLayout(0);

    QDialogButtonBox *dialogButtonBox = new QDialogButtonBox();

    dialogButtonBox->addButton(QDialogButtonBox::Ok);
    connect(dialogButtonBox,SIGNAL(clicked(QAbstractButton*)),
            aboutDialog,SLOT(close()));

    QQuickView *aboutView = new QQuickView(QUrl("qrc:qml/helpAbout.qml"));
    QQuickItem *qmlObject = aboutView->rootObject();
    qmlObject->setProperty("color",aboutDialog->palette().color(QPalette::Window));
    qmlObject->setProperty("bgColor",aboutDialog->palette().color(QPalette::Window));
    qmlObject->setProperty("version",QString::number(Globals::version));

    aboutView->setResizeMode(QQuickView::SizeRootObjectToView);

    QWidget *aboutWidget = QWidget::createWindowContainer(aboutView,0);
    aboutWidget->setPalette(aboutDialog->palette());
    aboutWidget->setAutoFillBackground(false);
    aboutDialog->setLayout(aboutLayout);

    aboutLayout->addWidget(aboutWidget,1);
    aboutLayout->addWidget(dialogButtonBox,0);
    aboutDialog->resize(500,400);
    aboutDialog->setWindowTitle(GUI::Globals::appName);
    aboutDialog->exec();
    aboutDialog->deleteLater();

}