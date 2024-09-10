	const wchar_t* GameObjectComponent::GetVersionString()
	{
		return GetVersion().AsWString().c_str();
	}