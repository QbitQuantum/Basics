void MobileApp::updateDownloadableList()
{
    QList <QString> dl;
    groups.clear();

    ReadFileToList(SAVEDBOOKLIST, dl, "UTF-8");
    parseDLFile(dl);

    //show aprorpriate widgets
    ui->downloadSTKWidget->setCurrentIndex(1);


    //Clear the old list
    ui->downloadListWidget->clear();

    //Build the new list
    for (int i=0; i<groups.size(); i++)
    {
        if (groups[i].downloadState != 0)
        {
            QListWidgetItem *lwi;
            lwi= new QListWidgetItem(groups[i].name + " (" + QString::number(groups[i].downloadSize)
                                     + /* "/" + QString::number(groups[i].fullSize) + */ " MB)");
            if (autoInstallKukBooksFlag && groups[i].name.contains("הרחבה"))
                lwi->setCheckState(Qt::Checked);
            else
                lwi->setCheckState(Qt::Unchecked);
            lwi->setWhatsThis(stringify(i));
            lwi->setToolTip("False");
            if(groups[i].hidden)
                lwi->setTextColor(QColor("gray"));

            ui->downloadListWidget->addItem(lwi);
            ui->downloadListWidget->setEnabled(true);
        }
    }

    if(autoInstallKukBooksFlag)
        downloadStart();

}