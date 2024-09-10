/**
 * Renames the note subfolder in the file system
 */
bool NoteSubFolder::rename(QString newName) {
    QDir dir = this->dir();

    if (dir.exists() && !newName.isEmpty()) {
        QString oldPath = fullPath();
        QString oldRelativePath = relativePath();
        setName(newName);
        QString newPath = fullPath();
        QString newRelativePath = relativePath();

        // rename the note sub folder paths of note tag links
        // (needs to be done before the folder rename because folder renaming
        // will cause a reload which would trigger the removal of the tag links)
        Tag::renameNoteSubFolderPathsOfLinks(oldRelativePath, newRelativePath);

        // rename the note subfolder
        return dir.rename(oldPath, newPath);
    }

    return false;
}