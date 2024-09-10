void QgsLocatorWidget::updateResults( const QString &text )
{
  if ( mLocator->isRunning() )
  {
    // can't do anything while a query is running, and can't block
    // here waiting for the current query to cancel
    // so we queue up this string until cancel has happened
    mLocator->cancelWithoutBlocking();
    mNextRequestedString = text;
    mHasQueuedRequest = true;
    return;
  }
  else
  {
    mHasSelectedResult = false;
    mLocatorModel->deferredClear();
    mLocator->fetchResults( text, createContext() );
  }
}