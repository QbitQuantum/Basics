// Checked: 2010-03-14 (RLVa-1.1.3a) | Added: RLVa-1.2.0a
void RlvRenameOnWearObserver::doneIdle()
{
	const LLViewerInventoryCategory* pRlvRoot = NULL; LLVOAvatar* pAvatar = gAgentAvatarp;
	if ( (RlvSettings::getEnableSharedWear()) || (!RlvSettings::getSharedInvAutoRename()) || (LLStartUp::getStartupState() < STATE_STARTED) || 
		 (!pAvatar) || ((pRlvRoot = RlvInventory::instance().getSharedRoot()) == NULL) )
	{
		delete this;
		return;
	}

	const LLViewerJointAttachment* pAttachPt = NULL; S32 idxAttachPt = 0;
//	RLV_ASSERT(mComplete.size() > 0);	// Catch instances where we forgot to call startFetch()
	for (uuid_vec_t::const_iterator itItem = mComplete.begin(); itItem != mComplete.end(); ++itItem)
	{
		const LLUUID& idAttachItem = *itItem;

		// If the item resides under #RLV we'll rename it directly; otherwise settle for "renaming" all of its links residing under #RLV
		LLInventoryModel::item_array_t items;
		if (gInventory.isObjectDescendentOf(idAttachItem, pRlvRoot->getUUID()))
			items.push_back(gInventory.getItem(idAttachItem));
		else
			items = gInventory.collectLinkedItems(idAttachItem, pRlvRoot->getUUID());
		if (items.empty())
			continue;

		if ( ((pAttachPt = pAvatar->getWornAttachmentPoint(idAttachItem)) == NULL) ||
			 ((idxAttachPt = RlvAttachPtLookup::getAttachPointIndex(pAttachPt)) == 0) )
		{
//			RLV_ASSERT(false);
			continue;
		}

		static const std::string &new_category_name = LLViewerFolderType::lookupNewCategoryName(LLFolderType::FT_NONE);
		for (S32 idxItem = 0, cntItem = items.count(); idxItem < cntItem; idxItem++)
		{
			LLViewerInventoryItem* pItem = items.get(idxItem);
			if (!pItem)
				continue;

			S32 idxAttachPtItem = RlvAttachPtLookup::getAttachPointIndex(pItem);
			if ( (idxAttachPt == idxAttachPtItem) || (idxAttachPtItem) )
				continue;

			std::string strAttachPt = pAttachPt->getName();
			LLStringUtil::toLower(strAttachPt);

			// If we can modify the item then we rename it directly, otherwise we create a new folder and move it
			if (pItem->getPermissions().allowModifyBy(gAgent.getID()))
			{
				std::string strName = pItem->getName();
				LLStringUtil::truncate(strName, DB_INV_ITEM_NAME_STR_LEN - strAttachPt.length() - 3);

				strName += " (" + strAttachPt + ")";

				pItem->rename(strName);
				pItem->updateServer(FALSE);
				gInventory.addChangedMask(LLInventoryObserver::LABEL, pItem->getUUID());
			}
			else
			{
				// Don't do anything if the item is a direct descendant of the shared root, or a folded folder
				LLViewerInventoryCategory* pFolder = gInventory.getCategory(pItem->getParentUUID());
				if ( (pFolder) && (pFolder->getUUID() != pRlvRoot->getUUID()) && (!RlvInventory::isFoldedFolder(pFolder, false)) )
				{
					std::string strFolderName = ".(" + strAttachPt + ")";

					// Rename the item's parent folder if it's called "New Folder", isn't directly under #RLV and contains exactly 1 object
					if ( (new_category_name == pFolder->getName()) && 
						 (pFolder->getParentUUID() != pRlvRoot->getUUID()) && 
						 (1 == RlvInventory::getDirectDescendentsCount(pFolder, LLAssetType::AT_OBJECT)) )
					{
						pFolder->rename(strFolderName);
						pFolder->updateServer(FALSE);
						gInventory.addChangedMask(LLInventoryObserver::LABEL, pFolder->getUUID());
					}
					else
					{
						// "No modify" item with a non-renameable parent: create a new folder named and move the item into it
						LLUUID idAttachFolder = gInventory.createNewCategory(pFolder->getUUID(), LLFolderType::FT_NONE, strFolderName);
						move_inventory_item(gAgent.getID(), gAgent.getSessionID(), pItem->getUUID(), idAttachFolder, std::string(), NULL);
					}
				}
			}
		}
	}
	gInventory.notifyObservers();

	delete this;
}