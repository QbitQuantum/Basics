void LLInventoryCategoriesObserver::changed(U32 mask)
{
	if (!mCategoryMap.size())
		return;

	std::vector<LLUUID> deleted_categories_ids;

	for (category_map_t::iterator iter = mCategoryMap.begin();
		 iter != mCategoryMap.end();
		 ++iter)
	{
		const LLUUID& cat_id = (*iter).first;
		LLCategoryData& cat_data = (*iter).second;
        
		LLViewerInventoryCategory* category = gInventory.getCategory(cat_id);
		if (!category)
        {
            LL_WARNS() << "Category : Category id = " << cat_id << " disappeared" << LL_ENDL;
			cat_data.mCallback();
            // Keep track of those deleted categories so we can remove them
            deleted_categories_ids.push_back(cat_id);
			continue;
        }

		const S32 version = category->getVersion();
		const S32 expected_num_descendents = category->getDescendentCount();
		if ((version == LLViewerInventoryCategory::VERSION_UNKNOWN) ||
			(expected_num_descendents == LLViewerInventoryCategory::DESCENDENT_COUNT_UNKNOWN))
		{
			continue;
		}

		// Check number of known descendents to find out whether it has changed.
		LLInventoryModel::cat_array_t* cats;
		LLInventoryModel::item_array_t* items;
		gInventory.getDirectDescendentsOf(cat_id, cats, items);
		if (!cats || !items)
		{
			LL_WARNS() << "Category '" << category->getName() << "' descendents corrupted, fetch failed." << LL_ENDL;
			// NULL means the call failed -- cats/items map doesn't exist (note: this does NOT mean
			// that the cat just doesn't have any items or subfolders).
			// Unrecoverable, so just skip this category.

			llassert(cats != NULL && items != NULL);

			continue;
		}
		
		const S32 current_num_known_descendents = cats->size() + items->size();

		bool cat_changed = false;

		// If category version or descendents count has changed
		// update category data in mCategoryMap
		if (version != cat_data.mVersion || current_num_known_descendents != cat_data.mDescendentsCount)
		{
			cat_data.mVersion = version;
			cat_data.mDescendentsCount = current_num_known_descendents;
			cat_changed = true;
		}

		// If any item names have changed, update the name hash 
		// Only need to check if (a) name hash has not previously been
		// computed, or (b) a name has changed.
		if (!cat_data.mIsNameHashInitialized || (mask & LLInventoryObserver::LABEL))
		{
			LLMD5 item_name_hash = gInventory.hashDirectDescendentNames(cat_id);
			if (cat_data.mItemNameHash != item_name_hash)
			{
				cat_data.mIsNameHashInitialized = true;
				cat_data.mItemNameHash = item_name_hash;
				cat_changed = true;
			}
		}

		// If anything has changed above, fire the callback.
		if (cat_changed)
			cat_data.mCallback();
	}
    
    // Remove deleted categories from the list
 	for (std::vector<LLUUID>::iterator deleted_id = deleted_categories_ids.begin(); deleted_id != deleted_categories_ids.end(); ++deleted_id)
	{
		removeCategory(*deleted_id);
    }
}