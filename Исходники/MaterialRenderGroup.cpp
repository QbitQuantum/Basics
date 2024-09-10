bool MaterialRenderGroup::Uninitialize()
{
	FOR_EACH_ITEM_TO(mGroups, Uninitialize());

	FOR_EACH_ITEM_CLEAR(mGroups, StateRenderGroupPool::Instance().Recycle);
	SAFE_RELEASE(mMaterial);

	return true;
}