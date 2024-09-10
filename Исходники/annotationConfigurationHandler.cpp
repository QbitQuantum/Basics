bool AnnotationConfigurationHandler::startElement( 
    const QString & /* namespaceURI */,
    const QString & /* localName */,
    const QString &qName,
    const QXmlAttributes &attributes )
{
  if ( !metAnnotationConfigurationTag && qName != "annotationConfiguration" )
  {
    errorStr = QObject::tr( "The file is not an Annotation Configuration file." );
    return false;
  }

  if ( qName == "annotationConfiguration" )
  {
    metAnnotationConfigurationTag = true;
  }
  else if ( qName == "entity" )
  {
    QListWidgetItem *item = new QListWidgetItem(listWidget);
    item->setFlags( item->flags() | Qt::ItemIsEditable );
    if (m_isEditor)
    {
      item->setFlags( item->flags() | Qt::ItemIsUserCheckable);
    }
    item->setText( attributes.value( "name" ) );
    QColor color( attributes.value( "color" ) );
    QColor white( Qt::white );
    QBrush brush( color );
    
    colors->push_back( QColor( attributes.value( "color" ).toLower() ) );
    (*colorNames2EntityTypes)[attributes.value( "color" ).toLower()] = attributes.value( "name" );
    /// @todo setBackgroundColor is deprecated in QT 4.2, replace by
    /// setBackground below after upgrading.
    /// item->setBackgroundColor  ( QColor( attributes.value( "color" ) ) );
    if (attributes.value("recursive") == "true")
    {
      m_recursiveEntityTypes->push_back(attributes.value( "name" ));
      QFont font = item->font();
      font.setItalic(true);
      font.setBold(true);
      item->setFont(font);
      if (m_isEditor)
      {
        item->setCheckState(Qt::Checked);
      }
    }
    else
    {
      if (m_isEditor)
      {
        item->setCheckState(Qt::Unchecked);
      }
    }
    item->setBackground  ( brush );
    item->setTextColor  ( white );
  }

  return true;
}