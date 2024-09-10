Dictionary::Ptr DynamicObject::Serialize(int attributeTypes) const
{
	Dictionary::Ptr update = boost::make_shared<Dictionary>();

	ASSERT(!OwnsLock());
	ObjectLock olock(this);

	InternalSerialize(update, attributeTypes);

	/* Make sure our own InternalSerialize() method was called. */
	ASSERT(update->Contains("__marker"));
	update->Remove("__marker");

	return update;
}