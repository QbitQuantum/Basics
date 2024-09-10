bool Helium::AssetIdentifier::Identify( const Reflect::ObjectPtr& object, Name* identity )
{
	Asset *pAsset = Reflect::SafeCast<Asset>(object);

	if ( pAsset )
	{
		if ( identity )
		{
			identity->Set(pAsset->GetPath().ToString());
			HELIUM_TRACE( TraceLevels::Info, "Identifying object [%s]\n", identity->Get() );
		}

		return true;
	}
	else if ( object )
	{
		HELIUM_TRACE( TraceLevels::Info, "Deferring identification of object of type [%s]\n", object->GetMetaClass()->m_Name );
	}

	return false;
}