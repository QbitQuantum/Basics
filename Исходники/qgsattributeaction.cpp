bool QgsAttributeAction::readXML( const QDomNode& layer_node )
{
  mActions.clear();

  QDomNode aaNode = layer_node.namedItem( "attributeactions" );

  if ( !aaNode.isNull() )
  {
    QDomNodeList actionsettings = aaNode.childNodes();
    for ( unsigned int i = 0; i < actionsettings.length(); ++i )
    {
      QDomElement setting = actionsettings.item( i ).toElement();
      addAction(( QgsAction::ActionType ) setting.attributeNode( "type" ).value().toInt(),
                setting.attributeNode( "name" ).value(),
                setting.attributeNode( "action" ).value(),
                setting.attributeNode( "capture" ).value().toInt() != 0 );
    }
  }
  return true;
}