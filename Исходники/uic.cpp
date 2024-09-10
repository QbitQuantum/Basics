void Uic::registerDatabases( const QDomElement& e ) {
  QDomElement n;
  QDomNodeList nl;
  int i;
  nl = e.parentNode().toElement().elementsByTagName( "widget" );
  for ( i = 0; i < ( int ) nl.length(); ++i ) {
    n = nl.item( i ).toElement();
    QString conn = getDatabaseInfo( n, "connection" );
    QString tab = getDatabaseInfo( n, "table" );
    QString fld = getDatabaseInfo( n, "field" );
    if ( !conn.isNull() ) {
      dbConnections += conn;
      if ( !tab.isNull() ) {
        dbCursors[conn] += tab;
        if ( !fld.isNull() )
          dbForms[conn] += tab;
      }
    }
  }
}