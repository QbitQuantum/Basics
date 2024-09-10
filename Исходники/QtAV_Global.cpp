//TODO: auto add new depend libraries information
void about()
{
    //we should use new because a qobject will delete it's children
    QTextBrowser *viewQtAV = new QTextBrowser;
    QTextBrowser *viewFFmpeg = new QTextBrowser;
    viewQtAV->setOpenExternalLinks(true);
    viewFFmpeg->setOpenExternalLinks(true);
    viewQtAV->setHtml(aboutQtAV_HTML());
    viewFFmpeg->setHtml(aboutFFmpeg_HTML());
    QTabWidget *tab = new QTabWidget;
    tab->addTab(viewQtAV, "QtAV");
    tab->addTab(viewFFmpeg, "FFmpeg");
    QPushButton *btn = new QPushButton(QObject::tr("Ok"));
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(btn);
    QDialog dialog;
    dialog.setWindowTitle(QObject::tr("About") + "  QtAV");
    QVBoxLayout *layout = new QVBoxLayout;
    dialog.setLayout(layout);
    layout->addWidget(tab);
    layout->addLayout(btnLayout);
    QObject::connect(btn, SIGNAL(clicked()), &dialog, SLOT(accept()));
    dialog.exec();
}