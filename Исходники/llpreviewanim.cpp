void LLPreviewAnim::dupliAnim( void *userdata )
{


		LLPreviewAnim* self = (LLPreviewAnim*) userdata;

		//if(!self->childGetValue("Anim play btn").asBoolean())
		//{
		//	printchat("anim must be playing to copy by this method; please try again");
		//	LLPreviewAnim::playAnim( userdata );
		//	return;
		//}

		const LLInventoryItem *item = self->getItem();
		
		if(item)
		{
			if(self->mAnimBuffer == NULL) 
			{
			
				return;
			}
			
		
			LLKeyframeMotion* motionp = NULL;
			//LLBVHLoader* loaderp = NULL;

			LLAssetID			xMotionID;
			LLTransactionID		xTransactionID;

			// generate unique id for this motion
			xTransactionID.generate();
			xMotionID = xTransactionID.makeAssetID(gAgent.getSecureSessionID());
			motionp = (LLKeyframeMotion*)gAgent.getAvatarObject()->createMotion(xMotionID);
/*
			// pass animation data through memory buffer
			//loaderp->serialize(dp);
			gAgent.getAvatarObject()->startMotion(item->getAssetUUID());	
			LLVOAvatar* avatar = gAgent.getAvatarObject();
			LLMotion*   motion = avatar->findMotion(item->getAssetUUID());
			LLKeyframeMotion* tmp = (LLKeyframeMotion*)motion;

			S32 file_size = tmp->getFileSize();
			U8* buffer = new U8[file_size];

			LLDataPackerBinaryBuffer dp(buffer, file_size);*/
			LLDataPackerBinaryBuffer dp(self->mAnimBuffer, self->mAnimBufferSize);
			LLVOAvatar* avatar = gAgent.getAvatarObject();
			LLMotion*   motion = avatar->findMotion(item->getAssetUUID());
			LLKeyframeMotion* tmp = (LLKeyframeMotion*)motion;
			tmp->serialize(dp);
			dp.reset();
			BOOL success = motionp && motionp->deserialize(dp);

			//delete []buffer;

			if (success)
			{
				motionp->setName(item->getName());
				gAgent.getAvatarObject()->startMotion(xMotionID);

	////////////////////////////////////////////////////////////////////
			/*LLKeyframeMotion* */motionp = (LLKeyframeMotion*)gAgent.getAvatarObject()->findMotion(xMotionID);

			S32 file_size = motionp->getFileSize();
			U8* buffer = new U8[file_size];

			LLDataPackerBinaryBuffer dp(buffer, file_size);
			if (motionp->serialize(dp))
			{
				LLVFile file(gVFS, motionp->getID(), LLAssetType::AT_ANIMATION, LLVFile::APPEND);

				S32 size = dp.getCurrentSize();
				file.setMaxSize(size);
				if (file.write((U8*)buffer, size))
				{
					std::string name = item->getName();
					std::string desc = item->getDescription();
					upload_new_resource(xTransactionID, // tid
										LLAssetType::AT_ANIMATION,
										name,
										desc,
										0,
										LLAssetType::AT_NONE,
										LLInventoryType::IT_ANIMATION,
										PERM_NONE,PERM_NONE,PERM_NONE,
										name,0,10,0);
				}
				else
				{
					llwarns << "Failure writing animation data." << llendl;
					LLNotifications::instance().add("WriteAnimationFail");
				}
			}

			delete [] buffer;
			// clear out cache for motion data
			gAgent.getAvatarObject()->removeMotion(xMotionID);
			LLKeyframeDataCache::removeKeyframeData(xMotionID);
	////////////////////////////////////////////////////////////////////
			}

		}

}