void Notes::deleteNote(const QString& noteId)
{
    QDir dir = notesFolder();
    dir.remove(noteId);

    m_settings.remove(noteId);

    updateModel();
}