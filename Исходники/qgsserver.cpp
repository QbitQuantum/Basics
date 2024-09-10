void QgsServer::putenv( const QString &var, const QString &val )
{
#ifdef _MSC_VER
  _putenv_s( var.toStdString().c_str(), val.toStdString().c_str() );
#else
  setenv( var.toStdString().c_str(), val.toStdString().c_str(), 1 );
#endif
  sSettings.load( var );
}