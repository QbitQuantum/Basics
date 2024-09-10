void UserFiles::showNewDir(QList<QString> newDirList)
{
    QDialog *newDirDialog = new QDialog;
    QPushButton *ok = new QPushButton("Ok");
    QLabel *information = new QLabel;
    QVBoxLayout *informationLayout = new QVBoxLayout;

    QString path = newDirList.at(0);
    QString name = newDirList.at(1);
    QString status = newDirList.at(2);

    if(status == "0") information->setText("Diretorio criado com sucesso!");
    if(status == "1") information->setText("Voce nao esta logado!");
    if(status == "2") information->setText("Ocorreu erro no servidor!");


    informationLayout->addWidget(information);
    informationLayout->addWidget(ok);
    newDirDialog->setLayout(informationLayout);

    connect(ok,SIGNAL(clicked()),newDirDialog,SLOT(close()));

    newDirDialog->exec();

    QListWidgetItem *item = new QListWidgetItem(QIcon(":/images/folder.jpeg"),name,listWidget,2);
}