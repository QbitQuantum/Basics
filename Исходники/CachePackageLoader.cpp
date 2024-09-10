/// @copydoc PackageLoader::TryFinishLoadObject()
bool CachePackageLoader::TryFinishLoadObject( size_t requestId, AssetPtr& rspObject )
{
	HELIUM_ASSERT( requestId < m_loadRequests.GetSize() );
	HELIUM_ASSERT( m_loadRequests.IsElementValid( requestId ) );

	LoadRequest* pRequest = m_loadRequests[ requestId ];
	HELIUM_ASSERT( pRequest );
	if( !( pRequest->flags & LOAD_FLAG_PRELOADED ) )
	{
		return false;
	}

	// Sync on template and owner dependencies.
	AssetLoader* pAssetLoader = AssetLoader::GetInstance();
	HELIUM_ASSERT( pAssetLoader );

	if( IsValid( pRequest->ownerLoadIndex ) )
	{
		size_t linkLoadId = pRequest->ownerLoadIndex;
		if( IsValid( linkLoadId ) && !pAssetLoader->TryFinishLoad( linkLoadId, pRequest->spOwner ) )
		{
			return false;
		}

		SetInvalid( pRequest->ownerLoadIndex );
	}

	rspObject = pRequest->spObject;
	Asset* pObject = rspObject;
	if( pObject && ( pRequest->flags & LOAD_FLAG_ERROR ) )
	{
		pObject->SetFlags( Asset::FLAG_BROKEN );
	}

	if ( pObject->IsPackage() )
	{
		Package *pPackage = Reflect::AssertCast<Package>( pObject );
		pPackage->SetLoader( this );
	}

	pRequest->spObject.Release();

	HELIUM_ASSERT( IsInvalid( pRequest->asyncLoadId ) );
	HELIUM_ASSERT( !pRequest->pAsyncLoadBuffer );

	//pRequest->spTemplate.Release();
	pRequest->spOwner.Release();

	HELIUM_ASSERT( IsInvalid( pRequest->ownerLoadIndex ) );
	//HELIUM_ASSERT( IsInvalid( pRequest->templateLoadIndex ) );

	HELIUM_ASSERT( pObject || pRequest->pEntry );
	HELIUM_TRACE(
		TraceLevels::Debug,
		"CachePackageLoader::TryFinishLoadObject(): Load request for \"%s\" (ID: %" PRIuSZ ") synced.\n",
		*( pObject ? pObject->GetPath() : pRequest->pEntry->path ).ToString(),
		requestId );

	m_loadRequests.Remove( requestId );
	m_loadRequestPool.Release( pRequest );

	return true;
}