static bool removeDirectory(QString dirName)
{
    QDir dir(dirName);
    QString tmpdir ="";
    if(!dir.exists()){
        return false;
    }

    QFileInfoList fileInfoList = dir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.fileName()=="."|| fileInfo.fileName()=="..")
            continue;

        if(fileInfo.isDir()){
            tmpdir = dirName +("/")+ fileInfo.fileName();
            removeDirectory(tmpdir);
            dir.rmdir(fileInfo.fileName());/**< 移除子目录 */
        }
        else if(fileInfo.isFile()){
            QFile tmpFile(fileInfo.fileName());
            dir.remove(tmpFile.fileName());/**< 删除临时文件 */
        }
        else{
            ;
        }
    }

    dir.cdUp();            /**< 返回上级目录，因为只有返回上级目录，才可以删除这个目录 */
    if(dir.exists(dirName)){
        if(!dir.rmdir(dirName))
            return false;
    }
    return true;
}