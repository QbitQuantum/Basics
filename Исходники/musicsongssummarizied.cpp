void MusicSongsSummarizied::importOtherMusicSongs(const QStringList &filelist)
{
    MusicProgressWidget progress;
    progress.show();
    progress.setTitle(tr("Import File Mode"));
    progress.setRange(0, filelist.count());

    MusicSongTag tag;
    for(int i=0; i<filelist.count(); ++i)
    {
        tag.readFile(filelist[i]);
        QString time(tag.getLengthString());
        m_musicFileNames[0] << MusicSong(filelist[i], 0, time.left(time.lastIndexOf(':')), QString());
        progress.setValue(i + 1);
    }
    m_mainSongLists[0]->updateSongsFileName(m_musicFileNames[0]);
}