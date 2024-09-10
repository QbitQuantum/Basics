void
ScanProgressWidget::onNewTrack( const Track& t )
{
    
    int& i = count( t.artist() );
    i++;
    paths += t.url().path();

    m_artist_count = track_counts.size();
    m_track_count++;

    // so this is a time saving way to keep the list the size of the screen
    // it goes over a bit almost certainly, but it's ok
    if (paths.size() > 60)
        paths.pop_front();
    
    if (i == 1)
    {
        QObject* o = new ImageFucker( t.artist() );
        connect( o, SIGNAL(f****d()), SLOT(onImageFucked()) );
        o->setParent( this );
    }
}