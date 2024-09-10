bool EffectRenderGroup::Uninitialize()
{
	FOR_EACH_TO(mGroups, Uninitialize());

	FOR_EACH_ITEM_CLEAR(mGroups, MaterialRenderGroupPool::Instance().Recycle);
	return true;
}