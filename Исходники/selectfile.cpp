bool SelectFile::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    QFileInfo fi(sourceDir);

 qDebug() << sourceDir << toDir+fi.fileName();
    if(!QFile::copy(sourceDir, toDir+fi.fileName()))
    {
        delete createfile;
        return false;
    }
    delete createfile;

    return true;
}