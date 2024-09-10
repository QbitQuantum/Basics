/// Modify the name, owner, or instance index of this object.
///
/// @param[in] rParameters  Object rename parameters.
///
/// @return  True if this object was renamed successfully, false if not.
///
/// @see GetName(), GetOwner(), GetInstanceIndex()
bool Asset::Rename( const RenameParameters& rParameters )
{
	Name name = rParameters.name;
	Asset* pOwner = rParameters.spOwner;
	uint32_t instanceIndex = rParameters.instanceIndex;

	HELIUM_TRACE(
		TraceLevels::Debug,
		TXT("Asset::Rename(): Renaming object \"%s\" to \"%s\" (Old Owner: \"%s\". New Owner: \"%s\".)\n"),
		*m_name,
		*rParameters.name,
		m_spOwner.ReferencesObject() ? *m_spOwner->GetPath().ToString() : TXT("[none]"),
		rParameters.spOwner.ReferencesObject() ? *rParameters.spOwner->GetPath().ToString() : TXT("[none]"));

	// Only allow setting an empty name if no owner or instance index are given and this object has no children.
	if( name.IsEmpty() )
	{
		HELIUM_ASSERT( !pOwner );
		HELIUM_ASSERT( IsInvalid( instanceIndex ) );
		if( pOwner || IsValid( instanceIndex ) )
		{
			HELIUM_TRACE(
				TraceLevels::Error,
				( TXT( "Asset::Rename(): Objects cannot have name information cleared if being assigned an " )
				  TXT( "owner or instance index.\n" ) ) );

			return false;
		}

		HELIUM_ASSERT( !m_wpFirstChild );
		if( m_wpFirstChild )
		{
			HELIUM_TRACE(
				TraceLevels::Error,
				TXT( "Asset::Rename(): Cannot clear name information for objects with children.\n" ) );

			return false;
		}
	}

	// Don't allow setting the owner to ourself.
	if( pOwner == this )
	{
		HELIUM_TRACE( TraceLevels::Error, TXT( "Asset::Rename(): Cannot set the owner of an object to itself.\n" ) );

		return false;
	}

	// Don't allow setting the owner to an object with no name information.
	if( pOwner && pOwner->m_name.IsEmpty() )
	{
		HELIUM_TRACE(
			TraceLevels::Error,
			TXT( "Asset::Rename(): Cannot set the owner of an object to an object with no path information.\n" ) );

		return false;
	}

	if( IsPackage() )
	{
		// Don't allow package objects to be children of non-package objects.
		if( pOwner && !pOwner->IsPackage() )
		{
			HELIUM_TRACE(
				TraceLevels::Error,
				TXT( "Asset::Rename(): Cannot set a non-package as the owner of a package.\n" ) );

			return false;
		}

		// Don't allow instance indexing for packages.
		if( IsValid( instanceIndex ) )
		{
			HELIUM_TRACE(
				TraceLevels::Error,
				TXT( "Asset::Rename(): Instance indexing not supported for packages.\n" ) );

			return false;
		}
	}

	// Don't need to do anything if the name, owner, and instance index are not changing.
	if( name == m_name &&
		pOwner == m_spOwner &&
		( instanceIndex == m_instanceIndex || ( instanceIndex == INSTANCE_INDEX_AUTO && IsValid( m_instanceIndex ) ) ) )
	{
		return true;
	}

	// Hold onto a reference to the current owner until we return from this function.  This is done in case this object
	// has the last strong reference to it, in which case we would encounter a deadlock if clearing its reference while
	// we still have a write lock on the object list (object destruction also requires acquiring a write lock).
	AssetPtr spOldOwner = m_spOwner;

	{
		// Acquire a write lock on the object list to prevent objects from being added and removed as well as keep
		// objects from being renamed while this object is being renamed.
		ScopeWriteLock scopeLock( sm_objectListLock );

		// Get the list of children belonging to the new owner.
		AssetWPtr& rwpOwnerFirstChild = ( pOwner ? pOwner->m_wpFirstChild : sm_wpFirstTopLevelObject );

		// Don't check for name clashes if we're clearing the object path name information.
		if( !name.IsEmpty() )
		{
			// Resolve name clashes either through the instance index lookup map (if an instance index will be assigned)
			// or through a child object search (if no instance index will be used).
			if( IsValid( instanceIndex ) )
			{
				// Get the instance index map for the requested object name.
				ChildNameInstanceIndexMap& rNameInstanceIndexMap = GetNameInstanceIndexMap();
				HELIUM_ASSERT( sm_pEmptyNameInstanceIndexMap );
				HELIUM_ASSERT( sm_pEmptyInstanceIndexSet );

				sm_pEmptyNameInstanceIndexMap->First() = ( pOwner ? pOwner->GetPath() : AssetPath( NULL_NAME ) );
				sm_pEmptyInstanceIndexSet->First() = name;

				ChildNameInstanceIndexMap::Accessor childNameMapAccessor;
				rNameInstanceIndexMap.Insert( childNameMapAccessor, *sm_pEmptyNameInstanceIndexMap );

				NameInstanceIndexMap::Accessor indexSetAccessor;
				childNameMapAccessor->Second().Insert( indexSetAccessor, *sm_pEmptyInstanceIndexSet );

				InstanceIndexSet& rIndexSet = indexSetAccessor->Second();
				InstanceIndexSet::ConstAccessor indexAccessor;

				if( instanceIndex == INSTANCE_INDEX_AUTO )
				{
					// Pick an unused instance index.
					instanceIndex = 0;
					while( !rIndexSet.Insert( indexAccessor, instanceIndex ) )
					{
						++instanceIndex;
						HELIUM_ASSERT( instanceIndex < INSTANCE_INDEX_AUTO );
					}
				}
				else
				{
					// Attempt to acquire the specified instance index.
					if( !rIndexSet.Insert( indexAccessor, instanceIndex ) )
					{
						HELIUM_TRACE(
							TraceLevels::Error,
							( TXT( "Asset::Rename(): Object already exists with the specified owner (%s), name " )
							  TXT( "(%s), and instance index (%" ) PRIu32 ").\n" ),
							( pOwner ? *pOwner->GetPath().ToString() : TXT( "none" ) ),
							*name,
							instanceIndex );

						return false;
					}
				}
			}
			else
			{
				// Check each child of the new owner for a name clash.
				for( Asset* pChild = rwpOwnerFirstChild; pChild != NULL; pChild = pChild->m_wpNextSibling )
				{
					if( pChild->m_name == name && pChild->m_instanceIndex == instanceIndex )
					{
						HELIUM_TRACE(
							TraceLevels::Error,
							( TXT( "Asset::Rename(): Object already exists with the specified owner (%s) and " )
							  TXT( "name (%s).\n" ) ),
							( pOwner ? *pOwner->GetPath().ToString() : TXT( "none" ) ),
							*name );

						return false;
					}
				}
			}
		}

		// Remove any old instance index tracking for the old path name.
		if( IsValid( m_instanceIndex ) )
		{
			AssetPath ownerPath = ( spOldOwner ? spOldOwner->GetPath() : AssetPath( NULL_NAME ) );

			ChildNameInstanceIndexMap& rNameInstanceIndexMap = GetNameInstanceIndexMap();

			ChildNameInstanceIndexMap::Accessor childMapAccessor;
			HELIUM_VERIFY( rNameInstanceIndexMap.Find( childMapAccessor, ownerPath ) );

			NameInstanceIndexMap& rNameMap = childMapAccessor->Second();
			NameInstanceIndexMap::Accessor nameMapAccessor;
			HELIUM_VERIFY( rNameMap.Find( nameMapAccessor, m_name ) );

			InstanceIndexSet& rIndexSet = nameMapAccessor->Second();
			HELIUM_VERIFY( rIndexSet.Remove( m_instanceIndex ) );

			/*
			if( rIndexSet.IsEmpty() )
			{
				HELIUM_VERIFY( rNameMap.Remove( nameMapAccessor ) );
				if( rNameMap.IsEmpty() )
				{
					HELIUM_VERIFY( rNameInstanceIndexMap.Remove( childMapAccessor ) );
				}
			}
			*/
		}

		// If the owner of this object is changing, remove this object from its old owner's list and add it to the new
		// owner.
		if( spOldOwner.Get() != pOwner || ( m_name.IsEmpty() ? !name.IsEmpty() : name.IsEmpty() ) )
		{
			// Object should not be in any child object lists if its name is empty.
			if( !m_name.IsEmpty() )
			{
				AssetWPtr& rwpOldOwnerFirstChild =
					( spOldOwner ? spOldOwner->m_wpFirstChild : sm_wpFirstTopLevelObject );

				Asset* pPreviousChild = NULL;
				Asset* pChild = rwpOldOwnerFirstChild;
				while( pChild )
				{
					if( pChild == this )
					{
						( pPreviousChild ? pPreviousChild->m_wpNextSibling : rwpOldOwnerFirstChild ) = m_wpNextSibling;
						m_wpNextSibling.Release();

						break;
					}

					pPreviousChild = pChild;
					pChild = pChild->m_wpNextSibling;
				}
			}

			// If you assert here, it's possible that sm_wpFirstTopLevelObject is null. This can happen if an asset is destroyed
			// after the asset system is shut down
			HELIUM_ASSERT( !m_wpNextSibling );

			// Only store the object in a child object list if it is being given a valid name.
			if( !name.IsEmpty() )
			{
				m_wpNextSibling = rwpOwnerFirstChild;
				rwpOwnerFirstChild = this;
			}
		}

		// Set the new path name.
		m_name = name;
		m_spOwner = pOwner;
		m_instanceIndex = instanceIndex;

		// Update path information for this object and its children.
		UpdatePath();
	}

	return true;
}