void Next2Friends::SaveApplicationData()
{
	Utils::StorageSetData(GetClsID(), GetVersion(), (void *)applicationData, sizeof(ApplicationData));
}