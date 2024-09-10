//------------------------------------------------------------------------------------------------
bool Vehicle::handleTyreCollision(OgreOde::Contact* contact)
{
	Geometry *geom = contact->getFirstGeometry();

	Object* pObject = (Object*) geom->getUserObject();
	if (pObject && 
		(pObject->getObjectType() == OgreOde_Prefab::ObjectType_Wheel))
	{
		((OgreOde_Prefab::Vehicle::Wheel*)(pObject))->setupTyreContact(contact);
		return true;
	}
	else
	{
		geom = contact->getSecondGeometry();
		pObject = (Object*) geom->getUserObject();
		if (pObject && (pObject->getObjectType() == OgreOde_Prefab::ObjectType_Wheel))
		{
			((OgreOde_Prefab::Vehicle::Wheel*)pObject)->setupTyreContact(contact);
			return true;
		}
	}
	return false;
}