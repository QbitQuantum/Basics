//???
void Photos::deleteImage()
{
    if( 0 == imageList.size())
    {
        QMessageBox::critical(this,tr("Warn"),
                              tr("No picture"),QMessageBox::Ok);
        return;
    }
    QMessageBox::StandardButton select = QMessageBox::question(NULL,"Warning",
                 tr("Delete is?"),QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if(QMessageBox::Yes == select)
    {

        imageList.takeAt(position);
        QDir dir(dirPath);
        QFileInfoList fileList;
        QFileInfo curFile;
        QStringList filters;

        filters << "*.jpg" << "*.JPG";

        //??их?
        fileList = dir.entryInfoList(filters, QDir::Dirs|QDir::Files
                                   | QDir::Readable | QDir::Writable
                                   | QDir::Hidden | QDir::NoDotAndDotDot
                                   , QDir::Name);

        if(fileList.size()>0)
        {

            curFile = fileList[position];
            QFile tmpFile(curFile.filePath());
            tmpFile.remove();
            fileList.removeAt(position);

        }

        if(0 == imageList.size())
        {

            QMessageBox::critical(this,tr("Warn"),
                                  tr("No more"),QMessageBox::Ok);
            return;
        }

        //???? ???■?????ш????????
        imagePath = imageList.at(position);
        setPixmap(imagePath);

    }
}