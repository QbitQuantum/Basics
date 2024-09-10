SVNHandler::FileStatus SVNHandler::fstatus( const QString& filename ) const
{
  // no valid repository
  if ( !_isPORepository )
    return NO_REPOSITORY;

  QString fn( filename );
  fn = fn.remove( QRegExp( "/$" ) );

  QFileInfo info( fn );

  // check if '.svn/entries' exists.
  QFile entries( info.dir( true ).path( ) + "/.svn/entries" );

  if ( !entries.exists() )
    return NOT_IN_SVN;

  KProcess proc;
  SVNOutputCollector out( &proc );

  proc << "svn" << "status" << "-v" << "--xml" << info.absFilePath();

  if( !proc.start( KProcess::Block, KProcess::Stdout ) )
    return ERROR_IN_WC;

  QDomDocument doc;
  QString errorMsg;
  int errorLine, errorCol;
  QDomNodeList nodelist;
  QDomNode node;
  QDomElement entry, wcStatus;

  // Parse the output.
  if ( !doc.setContent( out.getOutput(), &errorMsg, &errorLine, &errorCol ) ) {
    kdDebug(8109) << "Cannot parse \"svn status -v --xml\" output for"
        << filename << endl << "Line: " << errorLine << " Column: "
        << errorCol << " Error: " << errorMsg << endl;
    goto no_status_xml;
  }

  // There should be only one "entry" element. If it doesn't exist, path
  // isn't repo path at all.
  nodelist = doc.elementsByTagName("entry");
  if (nodelist.count() < 1)
    return NOT_IN_SVN;

  entry = nodelist.item(0).toElement();

  // Shouldn't fail, but just in case there is some weird error.
  if ( entry.attributeNode("path").value() != info.absFilePath() )
    return ERROR_IN_WC;

  for ( node = entry.firstChild(); !node.isNull(); node = node.nextSibling() ) {
    if ( !node.isElement() )
      continue;
    if (node.toElement().tagName() == "wc-status")
      break;
  }

  if ( node.isNull() )
    return ERROR_IN_WC;

  wcStatus = node.toElement();

  if ( wcStatus.attributeNode("item").value() == "normal" )
    return UP_TO_DATE;
  if ( wcStatus.attributeNode("item").value() == "modified" )
    return LOCALLY_MODIFIED;
  if ( wcStatus.attributeNode("item").value() == "conflicted" )
    return CONFLICT;
  if ( wcStatus.attributeNode("item").value() == "unversioned" )
    return NOT_IN_SVN;
  // TODO Ignored entry should have separate return value probably.
  if ( wcStatus.attributeNode("item").value() == "ignored" )
    return NOT_IN_SVN;
  if ( wcStatus.attributeNode("item").value() == "added" )
    return LOCALLY_ADDED;
  if ( wcStatus.attributeNode("item").value() == "deleted" )
    return LOCALLY_REMOVED;
  // TODO What to do with "missing", "incomplete", "replaced", "merged",
  // "obstructed", "external"? Can these appear at all in our case?

  return ERROR_IN_WC;

no_status_xml:
  if ( !entries.open( IO_ReadOnly ) )
    return ERROR_IN_WC;  // we already know that it is a repository

  // Parse the entries file
  if ( !doc.setContent( &entries, &errorMsg, &errorLine, &errorCol ) ) {
    kdDebug() << "Cannot parse .svn/entries file for " << filename << endl
        << "Line: " << errorLine << " Column: " << errorCol << " Error: " << errorMsg << endl;
    return ERROR_IN_WC;
  }
  entries.close();

  QDomElement element;
  // File name that we are searching
  const QString findName = info.fileName();
  // The entries are <entry> elements, so we have to check them
  QDomNode child = doc.documentElement().firstChild();
  for ( ; !child.isNull() ; child = child.nextSibling() )
  {
    if ( !child.isElement() )
      continue;
    element = child.toElement();
    if ( element.tagName() != "entry" ) {
      // We have another kind of element, so skip it
      // Should not happend with svn 1.1.x
      continue;
    }
    const QString name = element.attribute("name");
    if ( name == findName )
      break;
  }

  if ( child.isNull() ) {
    // We have not found an entry for the file
    return NOT_IN_SVN;
  }

  // ### TODO: should we check the attribute kind to be file and not dir?

  // ### TODO: what do copy and move add here?
  const QString onSchedule = element.attribute( "schedule" );
  if ( onSchedule == "delete" )
    return LOCALLY_REMOVED;
  else if ( onSchedule == "added" )
    return LOCALLY_ADDED;

  if ( element.hasAttribute( "conflict-new" ) || element.hasAttribute( "conflict-old" ) || element.hasAttribute( "conflict-wrk" ) ) {
    return CONFLICT;
  }

  // Note: we do not check the property time stamp
  const QString textTimeStamp( element.attribute( "text-time" ) );

  // calculate the UTC time from the file's last modified date
  struct stat st;
  lstat( QFile::encodeName(fn), &st );
  struct tm * tm_p = gmtime( &st.st_mtime );
  const int year = tm_p->tm_year + 1900;
  const int month = tm_p->tm_mon + 1;
  QString fileTime;
  fileTime.sprintf( "%04i-%02i-%02iT%02i:%02i:%02i.000000Z",
                    year, month, tm_p->tm_mday, tm_p->tm_hour, tm_p->tm_min, tm_p->tm_sec );
  //kdDebug() << "File: " << filename << " SVN time: " << textTimeStamp << " File time: " << fileTime << endl;
  if ( fileTime > textTimeStamp ) // ISO 8601 dates/times can be compared as strings if they have the exact same format.
    return LOCALLY_MODIFIED;

  return UP_TO_DATE;

}