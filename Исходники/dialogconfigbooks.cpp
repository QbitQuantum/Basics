void DialogConfigBooks::on_toolButtonGroupUpdat_clicked()
{
    QString groupPath=QDir::homePath()+"/.kirtasse/data/group.xml";
    QString groupPathOld=QDir::homePath()+"/.kirtasse/data/group.xml.old";
    QFile file;
    if(file.exists(groupPathOld)){
        if(file.exists(groupPath))
            file.remove(groupPath);

        file.rename(groupPathOld,groupPath);
            Messages->treeChargeGroupe( ui->treeWidgetBooks,0,true);
               ui->lineEditGroup->setText(groupPath);
    }else{
        QDir appDir(QCoreApplication::applicationDirPath() );
        appDir.cdUp();
        QString pathApp=  appDir.absolutePath()+"/share/elkirtasse";
          file.copy(pathApp+"/data/group.xml",groupPath);
    }
ui->toolButtonGroupUpdat->setEnabled(false);
}