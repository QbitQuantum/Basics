VectorIterator<Entity*> EntityList::filterByControllers(const BitSet &controllerIds)
{
	return filter( [=] (Entity *e) -> bool 
	{
		return controllerIds.intersects( e->getEntityType()->getControllers().getBitSet() );
	});
}