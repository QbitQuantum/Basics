/// Update processing of object property preloading for a given load request.
///
/// @param[in] pRequest  Load request to process.
///
/// @return  True if object property preloading for the given load request has completed, false if not.
bool LoosePackageLoader::TickDeserialize( LoadRequest* pRequest )
{
	HELIUM_ASSERT( pRequest );
	HELIUM_ASSERT( !( pRequest->flags & LOAD_FLAG_PROPERTY_PRELOADED ) );

	Asset* pObject = pRequest->spObject;

	HELIUM_ASSERT( pRequest->index < m_objects.GetSize() );
	SerializedObjectData& rObjectData = m_objects[ pRequest->index ];

	// Wait for the template and owner objects to load.
	AssetLoader* pAssetLoader = AssetLoader::GetStaticInstance();
	HELIUM_ASSERT( pAssetLoader );

	if( !rObjectData.templatePath.IsEmpty() )
	{
		if( IsValid( pRequest->templateLoadId ) )
		{
			if( !pAssetLoader->TryFinishLoad( pRequest->templateLoadId, pRequest->spTemplate ) )
			{
				return false;
			}

			SetInvalid( pRequest->templateLoadId );
		}

		if( !pRequest->spTemplate )
		{
			HELIUM_TRACE(
				TraceLevels::Error,
				TXT( "LoosePackageLoader: Failed to load template object for \"%s\".\n" ),
				*rObjectData.objectPath.ToString() );

			if( pObject )
			{
				pObject->SetFlags( Asset::FLAG_PRELOADED | Asset::FLAG_LINKED );
				pObject->ConditionalFinalizeLoad();
			}

			pRequest->flags |= LOAD_FLAG_PRELOADED | LOAD_FLAG_ERROR;

			return true;
		}
	}

	HELIUM_ASSERT( IsInvalid( pRequest->templateLoadId ) );
	Asset* pTemplate = pRequest->spTemplate;

	AssetPath ownerPath = rObjectData.objectPath.GetParent();
	if( !ownerPath.IsEmpty() )
	{
		if( IsValid( pRequest->ownerLoadId ) )
		{
			if( !pAssetLoader->TryFinishLoad( pRequest->ownerLoadId, pRequest->spOwner ) )
			{
				return false;
			}

			SetInvalid( pRequest->ownerLoadId );
		}

		if( !pRequest->spOwner )
		{
			HELIUM_TRACE(
				TraceLevels::Error,
				TXT( "LoosePackageLoader: Failed to load owner object for \"%s\".\n" ),
				*rObjectData.objectPath.ToString() );

			if( pObject )
			{
				pObject->SetFlags( Asset::FLAG_PRELOADED | Asset::FLAG_LINKED );
				pObject->ConditionalFinalizeLoad();
			}

			pRequest->flags |= LOAD_FLAG_PRELOADED | LOAD_FLAG_ERROR;

			return true;
		}
	}

	HELIUM_ASSERT( IsInvalid( pRequest->ownerLoadId ) );
	Asset* pOwner = pRequest->spOwner;

	AssetType* pType = pRequest->spType;
	HELIUM_ASSERT( pType );

	HELIUM_ASSERT( !pOwner || pOwner->IsFullyLoaded() );
	HELIUM_ASSERT( !pTemplate || pTemplate->IsFullyLoaded() );

	AsyncLoader& rAsyncLoader = AsyncLoader::GetStaticInstance();
	FilePath object_file_path = m_packageDirPath + *rObjectData.objectPath.GetName() + TXT( "." ) + Persist::ArchiveExtensions[ Persist::ArchiveTypes::Json ];

	bool load_properties_from_file = true;
	size_t object_file_size = 0;
	if ( !IsValid( pRequest->asyncFileLoadId ) )
	{
		if (!object_file_path.IsFile())
		{
			if (pType->GetMetaClass()->IsType( Reflect::GetMetaClass< Resource >() ))
			{
				HELIUM_TRACE(
					TraceLevels::Info,
					TXT( "LoosePackageLoader::TickDeserialize(): No object file found for resource \"%s\". Expected file location: \"%s\". This is normal for newly added resources.\n" ),
					*rObjectData.objectPath.ToString(),
					*object_file_path);

				// We will allow continuing to load using all default properties. This behavior is to support dropping resources into the 
				// data property and autogenerating objects from them.
				load_properties_from_file = false;
			}
			else
			{
				HELIUM_TRACE(
					TraceLevels::Warning,
					TXT( "LoosePackageLoader::TickDeserialize(): No object file found for object \"%s\". Expected file location: \"%s\"\n" ),
					*rObjectData.objectPath.ToString(),
					*object_file_path);
			}
		}
		else
		{
			Status status;
			status.Read( object_file_path.Get().c_str() );
			int64_t i64_object_file_size = status.m_Size;

			if( i64_object_file_size == -1 )
			{
				HELIUM_TRACE(
					TraceLevels::Warning,
					TXT( "LoosePackageLoader::TickDeserialize(): Could not get file size for object file of object \"%s\". Expected file location: \"%s\"\n" ),
					*rObjectData.objectPath.ToString(),
					*object_file_path );
			}
			else if( i64_object_file_size == 0 )
			{
				HELIUM_TRACE(
					TraceLevels::Warning,
					TXT( "LoosePackageLoader::TickDeserialize(): Object file \"%s\" for objct \"%s\" is empty.\n" ),
					*object_file_path,
					*rObjectData.objectPath.ToString() );
			}
			else if( static_cast< uint64_t >( i64_object_file_size ) > static_cast< uint64_t >( ~static_cast< size_t >( 0 ) ) )
			{
				HELIUM_TRACE(
					TraceLevels::Error,
					( TXT( "LoosePackageLoader::TickDeserialize(): Object file \"%s\" exceeds the maximum size supported by " )
					TXT( "the current platform (file size: %" ) PRIu64 TXT( " bytes; max supported: %" ) PRIuSZ
					TXT( " bytes).\n" ) ),
					object_file_path.c_str(),
					static_cast< uint64_t >( i64_object_file_size ),
					~static_cast< size_t >( 0 ) );
			}
			else
			{
				object_file_size = static_cast< size_t >(i64_object_file_size);
			}
		}
		
		if (!load_properties_from_file)
		{
			HELIUM_ASSERT(!object_file_size);
		}
		else if (!object_file_size)
		{
			pRequest->flags |= LOAD_FLAG_PRELOADED | LOAD_FLAG_ERROR;
			return true;
		}
		else
		{
			HELIUM_ASSERT( !pRequest->pAsyncFileLoadBuffer );
			pRequest->pAsyncFileLoadBuffer = DefaultAllocator().Allocate( object_file_size );
			HELIUM_ASSERT( pRequest->pAsyncFileLoadBuffer );

			pRequest->asyncFileLoadBufferSize = object_file_size;

			pRequest->asyncFileLoadId = rAsyncLoader.QueueRequest(
				pRequest->pAsyncFileLoadBuffer,
				String(object_file_path.c_str()),
				0,
				pRequest->asyncFileLoadBufferSize);
		}
		
	}
	
	size_t bytesRead = 0;
	if (load_properties_from_file)
	{
		HELIUM_ASSERT( IsValid( pRequest->asyncFileLoadId ) );

		if ( !rAsyncLoader.TrySyncRequest( pRequest->asyncFileLoadId, bytesRead ) )
		{
			return false;
		}
	}

	/////// POINT OF NO RETURN: We *will* return true after this point, and the object *will* be finished preloading,
	/////// for good or for bad.

	SetInvalid(pRequest->asyncFileLoadId);
	bool object_creation_failure = false;

	// If we already had an existing object, make sure the type and template match.
	if( pObject )
	{
		const AssetType* pExistingType = pObject->GetAssetType();
		HELIUM_ASSERT( pExistingType );
		if( pExistingType != pType )
		{
			HELIUM_TRACE(
				TraceLevels::Error,
				( TXT( "LoosePackageLoader: Cannot load \"%s\" using the existing object as the types do not match " )
				TXT( "(existing type: \"%s\"; serialized type: \"%s\".\n" ) ),
				*rObjectData.objectPath.ToString(),
				*pExistingType->GetName(),
				*pType->GetName() );

			pObject->SetFlags( Asset::FLAG_PRELOADED | Asset::FLAG_LINKED );
			pObject->ConditionalFinalizeLoad();
				
			object_creation_failure = true;
		}
	}
	else
	{
		bool bCreateResult = false;
		if (pRequest->forceReload)
		{
			// Create the object.
			bCreateResult = Asset::CreateObject(
				pRequest->spObject,
				pType,
				Name( NULL_NAME ),
				NULL,
				pTemplate );
		}
		else
		{
			// Create the object.
			bCreateResult = Asset::CreateObject(
				pRequest->spObject,
				pType,
				rObjectData.objectPath.GetName(),
				pOwner,
				pTemplate );
		}

		if( !bCreateResult )
		{
			HELIUM_TRACE(
				TraceLevels::Error,
				TXT( "LoosePackageLoader: Failed to create \"%s\" during loading.\n" ),
				*rObjectData.objectPath.ToString() );
				
			object_creation_failure = true;
		}

		pObject = pRequest->spObject;
		HELIUM_ASSERT( pObject );
	}

	if (load_properties_from_file && !object_creation_failure)
	{
		// Sanity checks for file load, then success path
		HELIUM_ASSERT( bytesRead == pRequest->asyncFileLoadBufferSize );
		if( IsInvalid( bytesRead ) )
		{
			HELIUM_TRACE(
				TraceLevels::Error,
				TXT( "LoosePackageLoader: Failed to read the contents of object file \"%s\" in async load request \"%d\".\n" ),
				object_file_path.c_str(),
				pRequest->asyncFileLoadId );
		}
		else if( bytesRead != pRequest->asyncFileLoadBufferSize )
		{
			HELIUM_TRACE(
				TraceLevels::Warning,
				( TXT( "LoosePackageLoader: Attempted to read %" ) PRIuSZ TXT( " bytes from object file \"%s\", " )
				TXT( "but only %" ) PRIuSZ TXT( " bytes were read.\n" ) ),
				pRequest->asyncFileLoadBufferSize,
				object_file_path.c_str(),
				bytesRead );
		}
		else
		{
			StaticMemoryStream archiveStream ( pRequest->pAsyncFileLoadBuffer, pRequest->asyncFileLoadBufferSize );

			HELIUM_TRACE(
				TraceLevels::Info,
				TXT( "LoosePackageLoader: Reading %s. pResolver = %x\n"), 
				object_file_path.c_str(),
				pRequest->pResolver);

			DynamicArray< Reflect::ObjectPtr > objects;
			objects.Push( pRequest->spObject.Get() ); // use existing objects
			Persist::ArchiveReaderJson::ReadFromStream( archiveStream, objects, pRequest->pResolver );
			HELIUM_ASSERT( objects[0].Get() == pRequest->spObject.Get() );
		}
	}

	if (load_properties_from_file)
	{
		DefaultAllocator().Free(pRequest->pAsyncFileLoadBuffer);
		pRequest->pAsyncFileLoadBuffer = NULL;
		pRequest->asyncFileLoadBufferSize = 0;
	}

	pRequest->flags |= LOAD_FLAG_PROPERTY_PRELOADED;

	if( object_creation_failure )
	{
		HELIUM_TRACE(
			TraceLevels::Error,
			TXT( "LoosePackageLoader: Deserialization of object \"%s\" failed.\n" ),
			*rObjectData.objectPath.ToString() );
		
		pObject->SetFlags( Asset::FLAG_PRELOADED | Asset::FLAG_LINKED );
		pObject->ConditionalFinalizeLoad();

		pRequest->flags |= LOAD_FLAG_ERROR;
	}
	else if( !pObject->IsDefaultTemplate() )
	{
		// If the object is a resource (not including the default template object for resource types), attempt to begin
		// loading any existing persistent resource data stored in the object cache.
		Resource* pResource = Reflect::SafeCast< Resource >( pObject );
		if( pResource )
		{
			Name objectCacheName = Name( HELIUM_ASSET_CACHE_NAME );
			CacheManager& rCacheManager = CacheManager::GetStaticInstance();

			Cache* pCache = rCacheManager.GetCache( objectCacheName );
			HELIUM_ASSERT( pCache );
			pCache->EnforceTocLoad();

			const Cache::Entry* pEntry = pCache->FindEntry( rObjectData.objectPath, 0 );
			if( pEntry && pEntry->size != 0 )
			{
				HELIUM_ASSERT( IsInvalid( pRequest->persistentResourceDataLoadId ) );
				HELIUM_ASSERT( !pRequest->pCachedObjectDataBuffer );

				pRequest->pCachedObjectDataBuffer =
					static_cast< uint8_t* >( DefaultAllocator().Allocate( pEntry->size ) );
				HELIUM_ASSERT( pRequest->pCachedObjectDataBuffer );
				pRequest->cachedObjectDataBufferSize = pEntry->size;

				AsyncLoader& rAsyncLoader = AsyncLoader::GetStaticInstance();
				pRequest->persistentResourceDataLoadId = rAsyncLoader.QueueRequest(
					pRequest->pCachedObjectDataBuffer,
					pCache->GetCacheFileName(),
					pEntry->offset,
					pEntry->size );
				HELIUM_ASSERT( IsValid( pRequest->persistentResourceDataLoadId ) );
			}
		}
	}

	if( IsInvalid( pRequest->persistentResourceDataLoadId ) )
	{
		// No persistent resource data needs to be loaded.
		pObject->SetFlags( Asset::FLAG_PRELOADED );
		pRequest->flags |= LOAD_FLAG_PERSISTENT_RESOURCE_PRELOADED;
	}

	// Asset is now preloaded.
	return true;
}