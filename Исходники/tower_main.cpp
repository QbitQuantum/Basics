void Tower::connectSubtower( SceneManager *scene, Tower *subtower )
{
	char name[30];
	sprintf( name, "Connector%d_%d\n", m_towerIndex, subtower->m_towerIndex );
	Entity *ent1 = scene->createEntity( name, "tube.mesh");

	sprintf( name, "Connector%d_%d\n", m_towerIndex, subtower->m_towerIndex );
	subtower->m_connectNode = scene->getRootSceneNode()->createChildSceneNode( name );
	subtower->m_connectNode->attachObject( ent1 );	

	Vector3 pos = getNode()->getPosition();
	Vector3 subPos = subtower->getNode()->getPosition();

	// align connector
	Vector3 connectPos = pos + subPos;
	connectPos *= 0.5;
	connectPos.y = 1.0;
	subtower->m_connectNode->setPosition( connectPos);

	Vector3 connectDir = pos - subPos;
	subtower->m_connectNode->setScale( 1.0, 1.0, connectDir.length() );
	connectDir.normalise();
	subtower->m_connectNode->setDirection( connectDir );

	subtower->m_upstreamTower = this;
}