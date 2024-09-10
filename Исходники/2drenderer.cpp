void TwoDRenderer::saveMap( QString filePath )
{
	QFile file( filePath );
	if( false == file.open(QFile::WriteOnly) )
		return;
		
	#define MAP_STRUCTURE "<?xml version=\"1.0\" ?>" \
								"<delleriumMap>" \
									"<walls></walls>" \
									"<bushes></bushes>" \
									"<me>" \
										"<balls></balls>" \
										"<targets></targets>" \
									"</me>" \
									"<enemy>" \
										"<balls></balls>" \
										"<targets></targets>" \
									"</enemy>" \
								"</delleriumMap>"
	
	// here we build the XML strucuture for the map
	QDomDocument domDocument;
	domDocument.setContent( QString(MAP_STRUCTURE) );

	QDomNode rootNode = domDocument.documentElement();

	QDomNode wallsNode = getChildByName( rootNode, "walls" );
	QDomNode bushesNode = getChildByName( rootNode, "bushes" );

	QDomNode meBallsNode = getChildByName( getChildByName(rootNode,"me"), "balls" );
	QDomNode meTargetsNode = getChildByName( getChildByName(rootNode,"me"), "targets" );
	
	QDomNode enemyBallsNode = getChildByName( getChildByName(rootNode,"enemy"), "balls" );
	QDomNode enemyTargetsNode = getChildByName( getChildByName(rootNode,"enemy"), "targets" );

	QList<QGraphicsItem*> gameObjects = _scene->items();
	foreach( QGraphicsItem* item, gameObjects )
	{
		GameObject* gameObject = static_cast<GameObject*>( item );
		if( 0 != gameObject )
		{
			switch( gameObject->getObjectType() )
			{
				case GameObject::ObjectWall:
					{
						QDomElement element = domDocument.createElement( "wall" );
						QDomAttr attributeX = domDocument.createAttribute( "x" ); attributeX.setValue( QString("%1").arg(gameObject->x()) );
						QDomAttr attributeY = domDocument.createAttribute( "y" ); attributeY.setValue( QString("%1").arg(gameObject->y()) );
						element.setAttributeNode( attributeX );
						element.setAttributeNode( attributeY );
						wallsNode.appendChild( element );
					}
					break;
					
				case GameObject::ObjectBush:
					{
						QDomElement element = domDocument.createElement( "bush" );
						QDomAttr attributeX = domDocument.createAttribute( "x" ); attributeX.setValue( QString("%1").arg(gameObject->x()) );
						QDomAttr attributeY = domDocument.createAttribute( "y" ); attributeY.setValue( QString("%1").arg(gameObject->y()) );
						element.setAttributeNode( attributeX );
						element.setAttributeNode( attributeY );
			
						bushesNode.appendChild( element );
					}
					break;
		
				case GameObject::ObjectBall:
					{
						QDomElement element = domDocument.createElement( "ball" );
						QDomAttr attributeX = domDocument.createAttribute( "x" ); attributeX.setValue( QString("%1").arg(gameObject->x()) );
						QDomAttr attributeY = domDocument.createAttribute( "y" ); attributeY.setValue( QString("%1").arg(gameObject->y()) );
						element.setAttributeNode( attributeX );
						element.setAttributeNode( attributeY );

						meBallsNode.appendChild( element );
					}
					break;
					
				case GameObject::ObjectTarget:
					{
						QDomElement element = domDocument.createElement( "target" );
						QDomAttr attributeX = domDocument.createAttribute( "x" ); attributeX.setValue( QString("%1").arg(gameObject->x()) );
						QDomAttr attributeY = domDocument.createAttribute( "y" ); attributeY.setValue( QString("%1").arg(gameObject->y()) );
						element.setAttributeNode( attributeX );
						element.setAttributeNode( attributeY );

						meTargetsNode.appendChild( element );
					}
					break;
		
				case GameObject::ObjectEnemyBall:
					{
						QDomElement element = domDocument.createElement( "ball" );
						QDomAttr attributeX = domDocument.createAttribute( "x" ); attributeX.setValue( QString("%1").arg(gameObject->x()) );
						QDomAttr attributeY = domDocument.createAttribute( "y" ); attributeY.setValue( QString("%1").arg(gameObject->y()) );
						element.setAttributeNode( attributeX );
						element.setAttributeNode( attributeY );

						enemyBallsNode.appendChild( element );
					}
					break;
					
				case GameObject::ObjectEnemyTarget:
					{
						QDomElement element = domDocument.createElement( "target" );
						QDomAttr attributeX = domDocument.createAttribute( "x" ); attributeX.setValue( QString("%1").arg(gameObject->x()) );
						QDomAttr attributeY = domDocument.createAttribute( "y" ); attributeY.setValue( QString("%1").arg(gameObject->y()) );
						element.setAttributeNode( attributeX );
						element.setAttributeNode( attributeY );

						enemyTargetsNode.appendChild( element );
					}
					break;
					
				case GameObject::ObjectNone:
				default:
					break;
			}
		}
	}