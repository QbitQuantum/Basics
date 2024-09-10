int KHelpNdxFile::Invoke() const
{
    return spawnlp( P_NOWAIT, _khneFound.strViewer.c_str(),
                              _khneFound.strViewer.c_str(),
                              _khneFound.strBook.c_str(),
                              _khneFound.strTopic.c_str(), 0 );
}