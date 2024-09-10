void QgsMapRendererParallelJob::renderLayerStatic( LayerRenderJob& job )
{
  if ( job.context.renderingStopped() )
    return;

  if ( job.cached )
    return;

#ifdef QGISDEBUG
  static QSet<QString> running;
  static QMultiMap<int, QString> elapsed;

  QSettings settings;
  bool log = settings.value( "/Map/logCanvasRefreshEvent", false ).toBool();

  QTime t;
  t.start();
  QgsDebugMsg( QString( "job %1 start" ).arg( reinterpret_cast< ulong >( &job ), 0, 16 ) );
  if ( log )
  {
    QgsMessageLog::logMessage( tr( "Layer %1 job started" ).arg( job.layerId ), tr( "Rendering" ) );
    Q_ASSERT( !running.contains( job.layerId ) );
    running << job.layerId;
  }
#endif

  try
  {
    job.renderer->render();
  }
  catch ( QgsException & e )
  {
    QgsDebugMsg( "Caught unhandled QgsException: " + e.what() );
  }
  catch ( std::exception & e )
  {
    QgsDebugMsg( "Caught unhandled std::exception: " + QString::fromAscii( e.what() ) );
  }
  catch ( ... )
  {
    QgsDebugMsg( "Caught unhandled unknown exception" );
  }

#ifdef QGISDEBUG
  int tt = t.elapsed();

  QgsDebugMsg( QString( "job %1 end [%2 ms]" ).arg( reinterpret_cast< ulong >( &job ), 0, 16 ).arg( tt ) );

  if ( log )
  {
    running.remove( job.layerId );
    elapsed.insert( tt, job.layerId );

    QgsMessageLog::logMessage( tr( "Layer %1 job ended (%2 ms; still running:%3)" ).arg( job.layerId ).arg( tt ).arg( QStringList( running.values() ).join( ", " ) ), tr( "Rendering" ) );
    if ( running.isEmpty() )
    {
      QList<int> tt( elapsed.keys() );
      qSort( tt.begin(), tt.end(), qGreater<int>() );
      Q_FOREACH ( int t, tt )
      {
        QgsMessageLog::logMessage( tr( "%1 ms: %2" ).arg( t ).arg( QStringList( elapsed.values( t ) ).join( ", " ) ), tr( "Rendering" ) );
      }
      QgsMessageLog::logMessage( "---", tr( "Rendering" ) );
      elapsed.clear();
    }