void FileInformation::getFileInformation()
{
    QFileInfo info(fileName);

    fileSize=info.size();
    QStringList list = fileName.split(".");
    fileType = list[1];
    fileName = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
    fileTime = getfiletime();
}