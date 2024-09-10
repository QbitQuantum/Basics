void QgsLocator::fetchResults( const QString &string, const QgsLocatorContext &context, QgsFeedback *feedback )
{
  // ideally this should not be required, as well behaved callers
  // will NOT fire up a new fetchResults call while an existing one is
  // operating/waiting to be canceled...
  cancelRunningQuery();

  // if no feedback object was passed, create one that is owned by this object
  // to ensure that filters ALWAYS receive a valid feedback
  if ( !feedback )
  {
    mOwnedFeedback.reset( new QgsFeedback() );
    feedback = mOwnedFeedback.get();
  }
  else
  {
    mOwnedFeedback.reset( nullptr );
  }
  mFeedback = feedback;

  QList< QgsLocatorFilter * > activeFilters;
  QString searchString = string;
  if ( searchString.indexOf( ' ' ) > 0 )
  {
    QString prefix = searchString.left( searchString.indexOf( ' ' ) );
    if ( mPrefixedFilters.contains( prefix ) && mPrefixedFilters.value( prefix )->enabled() )
    {
      activeFilters << mPrefixedFilters.value( prefix );
      searchString = searchString.mid( prefix.length() + 1 );
    }
  }
  if ( activeFilters.isEmpty() )
  {
    for ( QgsLocatorFilter *filter : qgis::as_const( mFilters ) )
    {
      if ( filter->useWithoutPrefix() && filter->enabled() )
        activeFilters << filter;
    }
  }

  QList< QgsLocatorFilter *> threadedFilters;
  for ( QgsLocatorFilter *filter : qgis::as_const( activeFilters ) )
  {
    std::unique_ptr< QgsLocatorFilter > clone( filter->clone() );
    connect( clone.get(), &QgsLocatorFilter::resultFetched, clone.get(), [this, filter]( QgsLocatorResult result )
    {
      result.filter = filter;
      emit filterSentResult( result );
    } );
    clone->prepare( searchString, context );

    if ( clone->flags() & QgsLocatorFilter::FlagFast )
    {
      // filter is fast enough to fetch results on the main thread
      clone->fetchResults( searchString, context, feedback );
    }
    else
    {
      // run filter in background
      threadedFilters.append( clone.release() );
    }
  }

  mActiveThreads.clear();
  for ( QgsLocatorFilter *filter : qgis::as_const( threadedFilters ) )
  {
    QThread *thread = new QThread();
    mActiveThreads.append( thread );
    filter->moveToThread( thread );
    connect( thread, &QThread::started, filter, [filter, searchString, context, feedback]
    {
      if ( !feedback->isCanceled() )
        filter->fetchResults( searchString, context, feedback );
      filter->emit finished();
    }, Qt::QueuedConnection );
    connect( filter, &QgsLocatorFilter::finished, thread, &QThread::quit );
    connect( filter, &QgsLocatorFilter::finished, filter, &QgsLocatorFilter::deleteLater );
    connect( thread, &QThread::finished, thread, [this, thread]
    {
      mActiveThreads.removeAll( thread );
      if ( mActiveThreads.empty() )
        emit finished();
    } );
    connect( thread, &QThread::finished, thread, &QThread::deleteLater );
    thread->start();
  }

  if ( mActiveThreads.empty() )
    emit finished();
}