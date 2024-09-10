void LLViewerObjectList::processObjectUpdate(LLMessageSystem *mesgsys,
											 void **user_data,
											 const EObjectUpdateType update_type,
											 bool cached, bool compressed)
{
	LLFastTimer t(LLFastTimer::FTM_PROCESS_OBJECTS);	
	
	LLVector3d camera_global = gAgent.getCameraPositionGlobal();
	LLViewerObject *objectp;
	S32			num_objects;
	U32			local_id;
	LLPCode		pcode = 0;
	LLUUID		fullid;
	S32			i;

	// figure out which simulator these are from and get it's index
	// Coordinates in simulators are region-local
	// Until we get region-locality working on viewer we
	// have to transform to absolute coordinates.
	num_objects = mesgsys->getNumberOfBlocksFast(_PREHASH_ObjectData);

	if (!cached && !compressed && update_type != OUT_FULL)
	{
		gTerseObjectUpdates += num_objects;
		S32 size;
		if (mesgsys->getReceiveCompressedSize())
		{
			size = mesgsys->getReceiveCompressedSize();
		}
		else
		{
			size = mesgsys->getReceiveSize();
		}
		// llinfos << "Received terse " << num_objects << " in " << size << " byte (" << size/num_objects << ")" << llendl;
	}
	else
	{
		S32 size;
		if (mesgsys->getReceiveCompressedSize())
		{
			size = mesgsys->getReceiveCompressedSize();
		}
		else
		{
			size = mesgsys->getReceiveSize();
		}

		// llinfos << "Received " << num_objects << " in " << size << " byte (" << size/num_objects << ")" << llendl;
		gFullObjectUpdates += num_objects;
	}

	U64 region_handle;
	mesgsys->getU64Fast(_PREHASH_RegionData, _PREHASH_RegionHandle, region_handle);
	LLViewerRegion *regionp = LLWorld::getInstance()->getRegionFromHandle(region_handle);

	if (!regionp)
	{
		llwarns << "Object update from unknown region! " << region_handle << llendl;
		return;
	}

	U8 compressed_dpbuffer[2048];
	LLDataPackerBinaryBuffer compressed_dp(compressed_dpbuffer, 2048);
	LLDataPacker *cached_dpp = NULL;
	
	for (i = 0; i < num_objects; i++)
	{
		LLTimer update_timer;
		BOOL justCreated = FALSE;

		if (cached)
		{
			U32 id;
			U32 crc;
			mesgsys->getU32Fast(_PREHASH_ObjectData, _PREHASH_ID, id, i);
			mesgsys->getU32Fast(_PREHASH_ObjectData, _PREHASH_CRC, crc, i);
		
			// Lookup data packer and add this id to cache miss lists if necessary.
			cached_dpp = regionp->getDP(id, crc);
			if (cached_dpp)
			{
				cached_dpp->reset();
				cached_dpp->unpackUUID(fullid, "ID");
				cached_dpp->unpackU32(local_id, "LocalID");
				cached_dpp->unpackU8(pcode, "PCode");
			}
			else
			{
				continue; // no data packer, skip this object
			}
		}
		else if (compressed)
		{
			U8							compbuffer[2048];
			S32							uncompressed_length = 2048;
			S32							compressed_length;
			compressed_dp.reset();

			U32 flags = 0;
			if (update_type != OUT_TERSE_IMPROVED)
			{
				mesgsys->getU32Fast(_PREHASH_ObjectData, _PREHASH_UpdateFlags, flags, i);
			}
			
			if (flags & FLAGS_ZLIB_COMPRESSED)
			{
				compressed_length = mesgsys->getSizeFast(_PREHASH_ObjectData, i, _PREHASH_Data);
				mesgsys->getBinaryDataFast(_PREHASH_ObjectData, _PREHASH_Data, compbuffer, 0, i);
				uncompressed_length = 2048;
				uncompress(compressed_dpbuffer, (unsigned long *)&uncompressed_length,
						   compbuffer, compressed_length);
				compressed_dp.assignBuffer(compressed_dpbuffer, uncompressed_length);
			}
			else
			{
				uncompressed_length = mesgsys->getSizeFast(_PREHASH_ObjectData, i, _PREHASH_Data);
				mesgsys->getBinaryDataFast(_PREHASH_ObjectData, _PREHASH_Data, compressed_dpbuffer, 0, i);
				compressed_dp.assignBuffer(compressed_dpbuffer, uncompressed_length);
			}


			if (update_type != OUT_TERSE_IMPROVED)
			{
				compressed_dp.unpackUUID(fullid, "ID");
				compressed_dp.unpackU32(local_id, "LocalID");
				compressed_dp.unpackU8(pcode, "PCode");
			}
			else
			{
				compressed_dp.unpackU32(local_id, "LocalID");
				getUUIDFromLocal(fullid,
								 local_id,
								 gMessageSystem->getSenderIP(),
								 gMessageSystem->getSenderPort());
				if (fullid.isNull())
				{
					// llwarns << "update for unknown localid " << local_id << " host " << gMessageSystem->getSender() << ":" << gMessageSystem->getSenderPort() << llendl;
					mNumUnknownUpdates++;
				}
			}
		}
		else if (update_type != OUT_FULL)
		{
			mesgsys->getU32Fast(_PREHASH_ObjectData, _PREHASH_ID, local_id, i);
			getUUIDFromLocal(fullid,
							local_id,
							gMessageSystem->getSenderIP(),
							gMessageSystem->getSenderPort());
			if (fullid.isNull())
			{
				// llwarns << "update for unknown localid " << local_id << " host " << gMessageSystem->getSender() << llendl;
				mNumUnknownUpdates++;
			}
		}
		else
		{
			mesgsys->getUUIDFast(_PREHASH_ObjectData, _PREHASH_FullID, fullid, i);
			mesgsys->getU32Fast(_PREHASH_ObjectData, _PREHASH_ID, local_id, i);
			// llinfos << "Full Update, obj " << local_id << ", global ID" << fullid << "from " << mesgsys->getSender() << llendl;
		}
		objectp = findObject(fullid);

		// This looks like it will break if the local_id of the object doesn't change
		// upon boundary crossing, but we check for region id matching later...
		// Reset object local id and region pointer if things have changed
		if (objectp && 
			((objectp->mLocalID != local_id) ||
			 (objectp->getRegion() != regionp)))
		{
			//if (objectp->getRegion())
			//{
			//	llinfos << "Local ID change: Removing object from table, local ID " << objectp->mLocalID 
			//			<< ", id from message " << local_id << ", from " 
			//			<< LLHost(objectp->getRegion()->getHost().getAddress(), objectp->getRegion()->getHost().getPort())
			//			<< ", full id " << fullid 
			//			<< ", objects id " << objectp->getID()
			//			<< ", regionp " << (U32) regionp << ", object region " << (U32) objectp->getRegion()
			//			<< llendl;
			//}
			removeFromLocalIDTable(*objectp);
			setUUIDAndLocal(fullid,
							local_id,
							gMessageSystem->getSenderIP(),
							gMessageSystem->getSenderPort());
			
			if (objectp->mLocalID != local_id)
			{    // Update local ID in object with the one sent from the region
				objectp->mLocalID = local_id;
			}
			
			if (objectp->getRegion() != regionp)
			{    // Object changed region, so update it
				objectp->setRegion(regionp);
				objectp->updateRegion(regionp); // for LLVOAvatar
			}
		}

		if (!objectp)
		{
			if (compressed)
			{
				if (update_type == OUT_TERSE_IMPROVED)
				{
					// llinfos << "terse update for an unknown object:" << fullid << llendl;
					continue;
				}
			}
			else if (cached)
			{
			}
			else
			{
				if (update_type != OUT_FULL)
				{
					// llinfos << "terse update for an unknown object:" << fullid << llendl;
					continue;
				}

				mesgsys->getU8Fast(_PREHASH_ObjectData, _PREHASH_PCode, pcode, i);
			}
#ifdef IGNORE_DEAD
			if (mDeadObjects.find(fullid) != mDeadObjects.end())
			{
				mNumDeadObjectUpdates++;
				// llinfos << "update for a dead object:" << fullid << llendl;
				continue;
			}
#endif

			objectp = createObject(pcode, regionp, fullid, local_id, gMessageSystem->getSender());
			if (!objectp)
			{
				continue;
			}
			justCreated = TRUE;
			mNumNewObjects++;
		}


		if (objectp->isDead())
		{
			llwarns << "Dead object " << objectp->mID << " in UUID map 1!" << llendl;
		}

		if (compressed)
		{
			if (update_type != OUT_TERSE_IMPROVED)
			{
				objectp->mLocalID = local_id;
			}
			processUpdateCore(objectp, user_data, i, update_type, &compressed_dp, justCreated);
			if (update_type != OUT_TERSE_IMPROVED)
			{
				objectp->mRegionp->cacheFullUpdate(objectp, compressed_dp);
			}
		}
		else if (cached)
		{
			objectp->mLocalID = local_id;
			processUpdateCore(objectp, user_data, i, update_type, cached_dpp, justCreated);
		}
		else
		{
			if (update_type == OUT_FULL)
			{
				objectp->mLocalID = local_id;
			}
			processUpdateCore(objectp, user_data, i, update_type, NULL, justCreated);
		}
		// <edit>
		if(justCreated && LLXmlImport::sImportInProgress)
		{
			if(objectp)
			{
				LLViewerObject* parent = (LLViewerObject*)objectp->getParent();
				if(parent)
				{
					if(parent->getID() == gAgent.getID())
					{
						LLXmlImport::onNewAttachment(objectp);
					}
				}
				else if( objectp->permYouOwner()
					&& (objectp->getPCode() == LLXmlImport::sSupplyParams->getPCode())
					&& (objectp->getScale() == LLXmlImport::sSupplyParams->getScale()))
				{
					LLXmlImport::onNewPrim(objectp);
				}
			}
		}
		// </edit>
	}

	LLVOAvatar::cullAvatarsByPixelArea();
}