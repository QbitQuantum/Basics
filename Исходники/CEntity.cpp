CEntity::~CEntity()
{
#if 0 && defined(NIV_DEBUG)
	CLogFile::Printf("CEntity[%d]::~CEntity()",m_ID);
#endif

	// Remove all children elements
	DeleteAllChildren();

	// remove the parent
	SetParent(NULL);

	// push the entity ID back into the pool
	CEntityIDs::Push(this);
}