void AISUpdate::doUpdate()
{
	// Do version/descendent accounting.
	for (std::map<LLUUID,S32>::const_iterator catit = mCatDescendentDeltas.begin();
		 catit != mCatDescendentDeltas.end(); ++catit)
	{
		LL_DEBUGS("Inventory") << "descendent accounting for " << catit->first << LL_ENDL;

		const LLUUID cat_id(catit->first);
		// Don't account for update if we just created this category.
		if (mCategoriesCreated.find(cat_id) != mCategoriesCreated.end())
		{
			LL_DEBUGS("Inventory") << "Skipping version increment for new category " << cat_id << LL_ENDL;
			continue;
		}

		// Don't account for update unless AIS told us it updated that category.
		if (mCatVersionsUpdated.find(cat_id) == mCatVersionsUpdated.end())
		{
			LL_DEBUGS("Inventory") << "Skipping version increment for non-updated category " << cat_id << LL_ENDL;
			continue;
		}

		// If we have a known descendent count, set that now.
		LLViewerInventoryCategory* cat = gInventory.getCategory(cat_id);
		if (cat)
		{
			S32 descendent_delta = catit->second;
			S32 old_count = cat->getDescendentCount();
			LL_DEBUGS("Inventory") << "Updating descendent count for "
								   << cat->getName() << " " << cat_id
								   << " with delta " << descendent_delta << " from "
								   << old_count << " to " << (old_count+descendent_delta) << LL_ENDL;
			LLInventoryModel::LLCategoryUpdate up(cat_id, descendent_delta);
			gInventory.accountForUpdate(up);
		}
		else
		{
			LL_DEBUGS("Inventory") << "Skipping version accounting for unknown category " << cat_id << LL_ENDL;
		}
	}

	// CREATE CATEGORIES
	for (deferred_category_map_t::const_iterator create_it = mCategoriesCreated.begin();
		 create_it != mCategoriesCreated.end(); ++create_it)
	{
		LLUUID category_id(create_it->first);
		LLPointer<LLViewerInventoryCategory> new_category = create_it->second;

		gInventory.updateCategory(new_category, LLInventoryObserver::CREATE);
		LL_DEBUGS("Inventory") << "created category " << category_id << LL_ENDL;
	}

	// UPDATE CATEGORIES
	for (deferred_category_map_t::const_iterator update_it = mCategoriesUpdated.begin();
		 update_it != mCategoriesUpdated.end(); ++update_it)
	{
		LLUUID category_id(update_it->first);
		LLPointer<LLViewerInventoryCategory> new_category = update_it->second;
		// Since this is a copy of the category *before* the accounting update, above,
		// we need to transfer back the updated version/descendent count.
		LLViewerInventoryCategory* curr_cat = gInventory.getCategory(new_category->getUUID());
		if (!curr_cat)
		{
			LL_WARNS("Inventory") << "Failed to update unknown category " << new_category->getUUID() << LL_ENDL;
		}
		else
		{
			new_category->setVersion(curr_cat->getVersion());
			new_category->setDescendentCount(curr_cat->getDescendentCount());
			gInventory.updateCategory(new_category);
			LL_DEBUGS("Inventory") << "updated category " << new_category->getName() << " " << category_id << LL_ENDL;
		}
	}

	// CREATE ITEMS
	for (deferred_item_map_t::const_iterator create_it = mItemsCreated.begin();
		 create_it != mItemsCreated.end(); ++create_it)
	{
		LLUUID item_id(create_it->first);
		LLPointer<LLViewerInventoryItem> new_item = create_it->second;

		// FIXME risky function since it calls updateServer() in some
		// cases.  Maybe break out the update/create cases, in which
		// case this is create.
		LL_DEBUGS("Inventory") << "created item " << item_id << LL_ENDL;
		gInventory.updateItem(new_item, LLInventoryObserver::CREATE);
	}
	
	// UPDATE ITEMS
	for (deferred_item_map_t::const_iterator update_it = mItemsUpdated.begin();
		 update_it != mItemsUpdated.end(); ++update_it)
	{
		LLUUID item_id(update_it->first);
		LLPointer<LLViewerInventoryItem> new_item = update_it->second;
		// FIXME risky function since it calls updateServer() in some
		// cases.  Maybe break out the update/create cases, in which
		// case this is update.
		LL_DEBUGS("Inventory") << "updated item " << item_id << LL_ENDL;
		//LL_DEBUGS("Inventory") << ll_pretty_print_sd(new_item->asLLSD()) << LL_ENDL;
		gInventory.updateItem(new_item);
	}

	// DELETE OBJECTS
	for (uuid_list_t::const_iterator del_it = mObjectsDeletedIds.begin();
		 del_it != mObjectsDeletedIds.end(); ++del_it)
	{
		LL_DEBUGS("Inventory") << "deleted item " << *del_it << LL_ENDL;
		gInventory.onObjectDeletedFromServer(*del_it, false, false, false);
	}

	// TODO - how can we use this version info? Need to be sure all
	// changes are going through AIS first, or at least through
	// something with a reliable responder.
	for (uuid_int_map_t::iterator ucv_it = mCatVersionsUpdated.begin();
		 ucv_it != mCatVersionsUpdated.end(); ++ucv_it)
	{
		const LLUUID id = ucv_it->first;
		S32 version = ucv_it->second;
		LLViewerInventoryCategory *cat = gInventory.getCategory(id);
		LL_DEBUGS("Inventory") << "cat version update " << cat->getName() << " to version " << cat->getVersion() << LL_ENDL;
		if (cat->getVersion() != version)
		{
			LL_WARNS() << "Possible version mismatch for category " << cat->getName()
					<< ", viewer version " << cat->getVersion()
					<< " server version " << version << LL_ENDL;
		}
	}

	gInventory.notifyObservers();
}