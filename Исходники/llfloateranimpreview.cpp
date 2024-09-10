//-----------------------------------------------------------------------------
// onBtnOK()
//-----------------------------------------------------------------------------
void LLFloaterAnimPreview::onBtnOK(void* userdata)
{
	LLFloaterAnimPreview* floaterp = (LLFloaterAnimPreview*)userdata;
	if (!floaterp->getEnabled()) return;

	if ((!floaterp->mInWorld && floaterp->mAnimPreview) || (floaterp->mInWorld && gAgent.getAvatarObject()))
	{
		LLKeyframeMotion* motionp;
		if (floaterp->mInWorld)
		{
			motionp = (LLKeyframeMotion*)gAgent.getAvatarObject()->findMotion(floaterp->mMotionID);
		}
		else
		{
			motionp = (LLKeyframeMotion*)floaterp->mAnimPreview->getDummyAvatar()->findMotion(floaterp->mMotionID);
		}

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
				std::string name = floaterp->childGetValue("name_form").asString();
				std::string desc = floaterp->childGetValue("description_form").asString();
				LLAssetStorage::LLStoreAssetCallback callback = NULL;
				S32 expected_upload_cost = sUploadAmount;
				void *userdata = NULL;
				upload_new_resource(floaterp->mTransactionID, // tid
						    LLAssetType::AT_ANIMATION,
						    name,
						    desc,
						    0,
						    LLAssetType::AT_NONE,
						    LLInventoryType::IT_ANIMATION,
						    LLFloaterPerms::getNextOwnerPerms(), LLFloaterPerms::getGroupPerms(), LLFloaterPerms::getEveryonePerms(),
						    name,
						    callback, expected_upload_cost, userdata);
			}
			else
			{
				llwarns << "Failure writing animation data." << llendl;
				LLNotifications::instance().add("WriteAnimationFail");
			}
		}

		delete [] buffer;
		// clear out cache for motion data
		if (floaterp->mInWorld)
		{
			gAgent.getAvatarObject()->removeMotion(floaterp->mMotionID);
			gAgent.getAvatarObject()->deactivateAllMotions();
		}
		else
		{
			floaterp->mAnimPreview->getDummyAvatar()->removeMotion(floaterp->mMotionID);
		}
		LLKeyframeDataCache::removeKeyframeData(floaterp->mMotionID);
	}

	floaterp->close(false);
}