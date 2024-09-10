void MusicSongsListPlayWidget::setParameter(const QString &name, const QString &path)
{
    MusicSongTag tag;
    if(tag.readFile(path))
    {
        m_totalTime = "/" + tag.getLengthString();
    }
    m_songNameLabel->setText(QFontMetrics(font()).elidedText(name, Qt::ElideRight, 180));
    m_songNameLabel->setToolTip(name);
    m_timeLabel->setText("00:00" + m_totalTime);

    if(!showArtPicture(name.split('-').front().trimmed()) &&
       !showArtPicture(name.split('-').back().trimmed()) )
    {
        m_artPictureLabel->setPixmap(QPixmap(":/share/defaultArt").scaled(60, 60));
    }
}