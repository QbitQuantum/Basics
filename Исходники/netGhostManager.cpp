void GhostManager::flushScopeAlwaysObjects()
{
   scopeAlwaysList.sort();

   SortableVector<AddListEntry>::iterator i;
   for(i = scopeAlwaysList.begin(); i != scopeAlwaysList.end(); i++)
   {
      if(!manager->registerObject((*i).obj))
      {
         if(!getLastError()[0])
            setLastError("Invalid packet.");
         return;
      }
      cleanupGroup->addObject((*i).obj);
      if((*i).obj->netFlags.test(SimNetObject::PolledGhost))
         owner->getEventManager()->addPolledObject((*i).obj);
   }
   scopeAlwaysList.clear();
   CSDelegate *delegate = (CSDelegate *) manager->findObject(SimCSDelegateId);
   if(delegate)
      delegate->onGhostAlwaysDone(getOwner());
}