bool KGrGameIO::safeRename (QWidget * theView, const QString & oldName,
                            const QString & newName)
{
    QFile newFile (newName);
    if (newFile.exists()) {
        // On some file systems we cannot rename if a file with the new name
        // already exists.  We must delete the existing file, otherwise the
        // upcoming QFile::rename will fail, according to Qt4 docs.  This
        // seems to be true with reiserfs at least.
        if (! newFile.remove()) {
            KGrMessage::information (theView, i18n ("Rename File"),
                i18n ("Cannot delete previous version of file '%1'.", newName));
            return false;
        }
    }
    QFile oldFile (oldName);
    if (! oldFile.rename (newName)) {
        KGrMessage::information (theView, i18n ("Rename File"),
            i18n ("Cannot rename file '%1' to '%2'.", oldName, newName));
        return false;
    }
    return true;
}