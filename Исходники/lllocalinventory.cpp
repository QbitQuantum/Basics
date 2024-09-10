//static
void LLLocalInventory::loadInvCache(std::string filename)
{
    std::string extension = gDirUtilp->getExtension(filename);
    std::string inv_filename = filename;
    if(extension == "gz")
    {
        LLUUID random;
        random.generate();
        inv_filename = filename.substr(0, filename.length() - 3) + "." + random.asString();

        if(!gunzip_file(filename, inv_filename))
        {
            // failure... message?
            return;
        }
    }

    LLInventoryModel::cat_array_t cats;
    LLInventoryModel::item_array_t items;
    bool is_cache_obsolete = false;
    if(LLInventoryModel::loadFromFile(inv_filename, cats, items, is_cache_obsolete))
    {
        // create a container category for everything
        LLViewerInventoryCategory* container = new LLViewerInventoryCategory(gAgent.getID());
        container->rename(gDirUtilp->getBaseFileName(filename, false));
        LLUUID container_id;
        container_id.generate();
        container->setUUID(container_id);
        container->setParent(gSystemFolderRoot);
        container->setPreferredType(LLFolderType::FT_NONE);
        LLInventoryModel::update_map_t container_update;
        ++container_update[container->getParentUUID()];
        gInventory.accountForUpdate(container_update);
        gInventory.updateCategory(container);
        gInventory.notifyObservers();

        LLViewerInventoryCategory* orphaned_items = new LLViewerInventoryCategory(gAgent.getID());
        orphaned_items->rename("Orphaned Items");
        LLUUID orphaned_items_id;

        orphaned_items_id.generate();
        orphaned_items->setUUID(orphaned_items_id);
        orphaned_items->setParent(container_id);
        orphaned_items->setPreferredType(LLFolderType::FT_NONE);

        LLInventoryModel::update_map_t orphaned_items_update;
        ++orphaned_items_update[orphaned_items->getParentUUID()];
        gInventory.accountForUpdate(orphaned_items_update);
        gInventory.updateCategory(orphaned_items);
        gInventory.notifyObservers();

        //conflict handling
        std::map<LLUUID,LLUUID> conflicting_cats;
        int dropped_cats = 0;
        int dropped_items = 0;

        // Add all categories
        LLInventoryModel::cat_array_t::iterator cat_iter = cats.begin();
        LLInventoryModel::cat_array_t::iterator cat_end = cats.end();
        for(; cat_iter != cat_end; ++cat_iter)
        {
            // Conditionally change its parent
            // Note: Should I search for missing parent id's?

            //if the parent is null, it goes in the very root of the tree!
            if((*cat_iter)->getParentUUID().isNull())
            {
                (*cat_iter)->setParent(container_id);
            }
            // If the parent exists and outside of pretend inventory, generate a new uuid
            else if(gInventory.getCategory((*cat_iter)->getParentUUID()))
            {
                if(!gInventory.isObjectDescendentOf((*cat_iter)->getParentUUID(), gSystemFolderRoot, TRUE))
                {
                    std::map<LLUUID,LLUUID>::iterator itr = conflicting_cats.find((*cat_iter)->getParentUUID());
                    if(itr == conflicting_cats.end())
                    {
                        dropped_cats++;
                        continue;
                    }
                    (*cat_iter)->setParent(itr->second);
                }
            } else {
                //well balls, this is orphaned.
                (*cat_iter)->setParent(orphaned_items_id);
            }
            // If this category already exists, generate a new uuid
            if(gInventory.getCategory((*cat_iter)->getUUID()))
            {
                LLUUID cat_random;
                cat_random.generate();
                conflicting_cats[(*cat_iter)->getUUID()] = cat_random;
                (*cat_iter)->setUUID(cat_random);
            }

            LLInventoryModel::update_map_t update;
            ++update[(*cat_iter)->getParentUUID()];
            gInventory.accountForUpdate(update);
            gInventory.updateCategory(*cat_iter);
            gInventory.notifyObservers();
        }

        // Add all items
        LLInventoryModel::item_array_t::iterator item_iter = items.begin();
        LLInventoryModel::item_array_t::iterator item_end = items.end();
        for(; item_iter != item_end; ++item_iter)
        {
            // Conditionally change its parent
            // Note: Should I search for missing parent id's?

            //if the parent is null, it goes in the very root of the tree!
            if((*item_iter)->getParentUUID().isNull())
            {
                (*item_iter)->setParent(container_id);
            }

            // If the parent exists and outside of pretend inventory, generate a new uuid
            if(gInventory.getCategory((*item_iter)->getParentUUID()))
            {
                if(!gInventory.isObjectDescendentOf((*item_iter)->getParentUUID(), gSystemFolderRoot, TRUE))
                {
                    std::map<LLUUID,LLUUID>::iterator itr = conflicting_cats.find((*item_iter)->getParentUUID());
                    if(itr == conflicting_cats.end())
                    {
                        dropped_items++;
                        continue;
                    }
                    (*item_iter)->setParent(itr->second);
                }
            } else {
                //well balls, this is orphaned.
                (*item_iter)->setParent(orphaned_items_id);
            }
            // Avoid conflicts with real inventory...
            // If this item id already exists, generate a new uuid
            if(gInventory.getItem((*item_iter)->getUUID()))
            {
                LLUUID item_random;
                item_random.generate();
                (*item_iter)->setUUID(item_random);
            }

            LLInventoryModel::update_map_t update;
            ++update[(*item_iter)->getParentUUID()];
            gInventory.accountForUpdate(update);
            gInventory.updateItem(*item_iter);
            gInventory.notifyObservers();
        }

        // Quality time
        if(dropped_items || dropped_cats)
        {
            std::ostringstream message;
            message << "Some items were ignored due to conflicts:\n\n";
            if(dropped_cats) message << dropped_cats << " folders\n";
            if(dropped_items) message << dropped_items << " items\n";

            LLSD args;
            args["ERROR_MESSAGE"] = message.str();
            LLNotificationsUtil::add("ErrorMessage", args);
        }
        conflicting_cats.clear();// srsly dont think this is need but w/e :D
    }

    // remove temporary unzipped file
    if(extension == "gz")
    {
        LLFile::remove(inv_filename);
    }

}