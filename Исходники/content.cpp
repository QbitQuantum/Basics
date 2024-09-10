/** \fn     Content::RenameFile(const QString &sStorageGroup,
 *                              const QString &sFileName,
 *                              const QString &sNewFile)
 *  \brief  Renames the file to the new name.
 *  \param  sStorageGroup The storage group name where the image is located
 *  \param  sFileName The filename including the path that shall be renamed
 *  \param  sNewName  The new name of the file (only the name, no path)
 *  \return bool True if renaming was successful, otherwise false
 */
bool Content::RenameFile( const QString &sStorageGroup,
                          const QString &sFileName,
                          const QString &sNewName)
{
    QFileInfo fi = QFileInfo();
    fi = GetFile(sStorageGroup, sFileName);

    // Check if the file exists and is writable.
    // Only then we can actually delete it.
    if (!fi.isFile() && !QFile::exists(fi.absoluteFilePath()))
    {
        LOG(VB_GENERAL, LOG_ERR, "RenameFile - File does not exist.");
        return false;
    }

    // Check if the new filename has no path stuff specified
    if (sNewName.contains("/") || sNewName.contains("\\"))
    {
        LOG(VB_GENERAL, LOG_ERR, "RenameFile - New file must not contain a path.");
        return false;
    }
    
    // The newly renamed file must be in the same path as the original one.
    // So we need to check if a file of the new name exists and would be 
    // overwritten by the new filename. To to this get the path from the 
    // original file and append the new file name, Then check 
    // if it exists in the given storage group
    
    // Get the everthing until the last directory separator
    QString path = sFileName.left(sFileName.lastIndexOf("/"));
    // Append the new file name to the path
    QString newFileName = path.append("/").append(sNewName);
    
    QFileInfo nfi = QFileInfo();
    nfi = GetFile(sStorageGroup, newFileName);
    
    // Check if the target file is already present.
    // If is there then abort, overwriting is not supported
    if (nfi.isFile() || QFile::exists(nfi.absoluteFilePath()))
    {
        LOG(VB_GENERAL, LOG_ERR,
            QString("RenameFile - New file %1 would overwrite "
                    "existing one, not renaming.").arg(sFileName));
        return false;
    }

    // All checks have been passed, rename the file
    QFile file; 
    file.setFileName(fi.fileName());
    QDir::setCurrent(fi.absolutePath());
    return file.rename(sNewName);
}