void RecoveryWidget::flashZip()
{
    if (QMessageBox::question(this, tr("Flash Zip"), tr("Are you sure??"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        return;
    this->romFileName = QFileDialog::getOpenFileName(this, tr("Open ROM File"), "/", tr("Zip files (*.zip)"));
    QFileInfo fInfo = QFileInfo(this->romFileName);
    FileList *fileList = new FileList;
    fileList->name.append(this->romFileName);
    fileList->size.append(QString::number(fInfo.size()));
    fileList->date.append(fInfo.lastModified().toString());
    fileList->type.append("file");
    this->romFileName = fInfo.fileName();

    QProcess tmp;
    tmp.start("\"" + sdk + "\"adb shell su -c 'mount /sdcard'");
    tmp.waitForFinished(-1);
    tmp.terminate();
//    if (this->dialog != NULL)
//        delete this->dialog;
//    this->dialog = new dialogKopiuj(this, fileList, this->sdk, dialogKopiuj::ComputerToPhone, fInfo.absolutePath(), "/sdcard/");
//    this->dialog=new dialogKopiuj(this,fileList,this->sdk,"computerToPhone",this->phone,NULL,this->computer);
//    if (this->alwaysCloseCopy)
//        this->dialog->closeAfterFinished();
//    if (this->dialogKopiujShowModal)
//        this->dialog->setModal(true);
//    this->dialog->show();


//    connect(this->dialog,SIGNAL(finished(int)),this,SLOT(flashZipCopied()));

    this->ui->stackedRecovery->setCurrentWidget(this->ui->pageFlashZIP);
}