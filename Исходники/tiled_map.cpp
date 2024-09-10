Object* TiledMap::registerObject(int tableRef)
{
	console.log(CON_LOG, CON_VDEBUG, "Registering object.");
	Object* newObject = new Object(tableRef, this);
	
	objects.push_back(newObject);
	newObject->initialize();

	return newObject;
}