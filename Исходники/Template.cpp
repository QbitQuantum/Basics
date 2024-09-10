void ProcessEnemies()
{
	//Do bullets
	list<cObject*>::iterator it;
	list<cObject*> removeList;
	for ( it=enemies.begin() ; it != enemies.end(); it++ )
	{
		cObject* obj = *it;
		if( obj->IsActivated == true && CanUpdate == true)
			obj->Update();
		if( obj->IsAlive )
			obj->Draw(backbuffer);
		else
		{
			removeList.push_back(obj);
		}
	}

	for ( it=removeList.begin() ; it != removeList.end(); it++ )
	{
		cObject* obj = *it;
		enemies.remove(obj);
		delete obj;
	}
}