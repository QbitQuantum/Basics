QString GRASS_EXPORT QgsGrass::openMapset( QString gisdbase, QString location, QString mapset )
{
  QgsDebugMsg( QString( "gisdbase = %1" ).arg( gisdbase.toUtf8().constData() ) );
  QgsDebugMsg( QString( "location = %1" ).arg( location.toUtf8().constData() ) );
  QgsDebugMsg( QString( "mapset = %1" ).arg( mapset.toUtf8().constData() ) );

  QString mapsetPath = gisdbase + "/" + location + "/" + mapset;

  // Check if the mapset is in use
  QString gisBase = getenv( "GISBASE" );
  if ( gisBase.isEmpty() ) return QObject::tr( "GISBASE is not set." );

  QFileInfo fi( mapsetPath + "/WIND" );
  if ( !fi.exists() )
  {
    return QObject::tr( "%1 is not a GRASS mapset." ).arg( mapsetPath );
  }
  QString lock = mapsetPath + "/.gislock";

#ifndef _MSC_VER
  int pid = getpid();
#else
  int pid = GetCurrentProcessId();
#endif

  QgsDebugMsg( QString( "pid = %1" ).arg( pid ) );

#ifndef Q_OS_WIN
  QFile lockFile( lock );
  QProcess *process = new QProcess();
  QString lockProgram( gisBase + "/etc/lock" );

  QgsDebugMsg( QString( "pid = %1" ).arg( pid ) );

  process->start( lockProgram, QStringList() << lock << QString::number( pid ) );
  if ( !process->waitForStarted() )
  {
    delete process;
    return QObject::tr( "Cannot start %1/etc/lock" ).arg( gisBase );
  }

  process->waitForFinished( -1 );

  int status = process->exitStatus();
  QgsDebugMsg( QString( "status = %1" ).arg( status ) );
  delete process;

  if ( status > 0 )
    return QObject::tr( "Mapset is already in use." );
#endif // !WIN32

  // Create temporary directory
  QFileInfo info( mapsetPath );
  QString user = info.owner();

  mTmp = QDir::tempPath() + "/grass6-" + user + "-" + QString::number( pid );
  QDir dir( mTmp );
  if ( dir.exists() )
  {
    QFileInfo dirInfo( mTmp );
    if ( !dirInfo.isWritable() )
    {
#ifndef Q_OS_WIN
      lockFile.remove();
#endif
      return QObject::tr( "Temporary directory %1 exists but is not writable" ).arg( mTmp );
    }
  }
  else if ( !dir.mkdir( mTmp ) )
  {
#ifndef Q_OS_WIN
    lockFile.remove();
#endif
    return QObject::tr( "Cannot create temporary directory %1" ).arg( mTmp );
  }

  // Create GISRC file
  QString globalGisrc =  QDir::home().path() + "/.grassrc6";
  mGisrc = mTmp + "/gisrc";

  QgsDebugMsg( QString( "globalGisrc = %1" ).arg( globalGisrc ) );
  QgsDebugMsg( QString( "mGisrc = %1" ).arg( mGisrc ) );

  QFile out( mGisrc );
  if ( !out.open( QIODevice::WriteOnly ) )
  {
#ifndef Q_OS_WIN
    lockFile.remove();
#endif
    return QObject::tr( "Cannot create %1" ).arg( mGisrc );
  }
  QTextStream stream( &out );

  QFile in( globalGisrc );
  QString line;
  bool guiSet = false;
  char buf[1000];
  if ( in.open( QIODevice::ReadOnly ) )
  {
    while ( in.readLine( buf, 1000 ) != -1 )
    {
      line = buf;
      if ( line.contains( "GISDBASE:" ) ||
           line.contains( "LOCATION_NAME:" ) ||
           line.contains( "MAPSET:" ) )
      {
        continue;
      }
      if ( line.contains( "GRASS_GUI:" ) ) guiSet = true;
      stream << line;
    }
    in.close();
  }
  line = "GISDBASE: " + gisdbase + "\n";
  stream << line;
  line = "LOCATION_NAME: " + location + "\n";
  stream << line;
  line = "MAPSET: " + mapset + "\n";
  stream << line;
  if ( !guiSet )
  {
    stream << "GRASS_GUI: wxpython\n";
  }

  out.close();

  // Set GISRC environment variable

  /* _Correct_ putenv() implementation is not making copy! */
  putEnv( "GISRC", mGisrc );

  // Reinitialize GRASS
  G__setenv( "GISRC", mGisrc.toUtf8().data() );
#if defined(WIN32)
  G__setenv( "GISDBASE", shortPath( gisdbase ).toLocal8Bit().data() );
#else
  G__setenv( "GISDBASE", gisdbase.toUtf8().data() );
#endif
  G__setenv( "LOCATION_NAME", location.toLocal8Bit().data() );
  G__setenv( "MAPSET", mapset.toLocal8Bit().data() );
  defaultGisdbase = gisdbase;
  defaultLocation = location;
  defaultMapset = mapset;

  active = true;

#ifndef Q_OS_WIN
  // Close old mapset
  if ( mMapsetLock.length() > 0 )
  {
    QFile file( mMapsetLock );
    file.remove();
  }
#endif

  mMapsetLock = lock;

  return NULL;
}