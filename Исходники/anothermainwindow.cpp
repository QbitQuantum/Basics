void AnotherMainWindow::DoTask()
{
    int t1s = QTime::currentTime().msec();
    QList<QString>* fList = new QList<QString>();
    DirWorker::FindFiles(_taskOptions->FromDir, "*.txt", fList);

    int len = fList->length();

    for(int i = 0; i < len; i++)
    {
        QString fName = fList->at(i);
        std::wstring sst = fName.toStdWString();
        LPCWSTR sourseFile =  sst.c_str();
        QString newFileQ(_taskOptions->ToDir + "\\" + QString::number(1) + '_' + QString::number(i) + ".html");
        std::wstring nst = newFileQ.toStdWString();
        LPCWSTR newFile = nst.c_str();
        if(!CopyFileW(sourseFile, newFile, false))
        {
            QMessageBox::critical(0, "Ошибка", "Не удалось скопировать файл: " + fName);
            return;
        }
        FileCreateParams* params = new FileCreateParams();
        params->CreateOptions = OPEN_EXISTING;
        params->DesiredAccess = GENERIC_READ;
        params->DesiredAccess += GENERIC_WRITE;
        params->FileName = newFileQ;
        FileWorker::OpenCreateFile(params);
        FileWorker::UpdateFile(params);
        FileWorker::CloseOpenedFile(params);
        delete params;
    }
    int t2s = QTime::currentTime().msec();
    ui->DurationBox->setText(QString::number(t2s - t1s));
}