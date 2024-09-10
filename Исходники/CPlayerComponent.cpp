// init
// run when init object
void CPlayerComponent::initComponent()
{
    m_collada = (CColladaMeshComponent*)m_gameObject->getComponent( IObjectComponent::ColladaMesh );

	// load model by character id
	CGameConfig::SCharacterInfo *charInfo = CGameConfig::getInstance()->getCharacterInfo(m_charID);

	// load model
	m_collada->loadScene(charInfo->model.c_str() );

	// load animation
	CColladaAnimationFactory* animFactory = CColladaAnimationFactory::getInstance();
	m_animationPackage = animFactory->getAnimation( charInfo->name.c_str() );
	if ( m_animationPackage == NULL )
		m_animationPackage = animFactory->loadAnimation( charInfo->name.c_str(), getIView()->getPath(charInfo->anim));
    m_collada->setAnimationPackage( m_animationPackage );
    
	// apply lod
	for (int i = 0, n = (int)charInfo->lods.size(); i < n; i++)	
		m_collada->addLodData( charInfo->lods[i].distance, charInfo->lods[i].node.c_str() );	

    init(m_gameObject);

	// register event
	getIView()->registerEvent("CPlayerComponent", this);

	// init lua player component
	char luaObjName[64];
	sprintf(luaObjName, "CPlayerComp_%ld", m_gameObject->getID());
	m_luaObjName = luaObjName;

	// init collision
	ISceneManager *smgr = getIView()->getSceneMgr();
	ITriangleSelector *selector = smgr->createTriangleSelectorFromBoundingBox(m_gameObject->getSceneNode());
	m_gameObject->getSceneNode()->setTriangleSelector(selector);
	selector->drop();

	CGameObject *zone = (CGameObject*)m_gameObject->getParent();
	if ( zone && zone->getObjectType() == CGameObject::ZoneObject )	
		((CZone*)zone)->registerCollideObj( m_gameObject);
		
}