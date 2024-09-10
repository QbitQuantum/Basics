	void inventory_object::test<6>()
	{
		LLPointer<LLInventoryItem> src = create_random_inventory_item();
		
		LLUUID new_item_id, new_parent_id;
		new_item_id.generate();
		src->setUUID(new_item_id);
		
		new_parent_id.generate();
		src->setParent(new_parent_id);
		
		std::string new_name = "LindenLab";
		src->rename(new_name);
		
		src->setType(LLAssetType::AT_SOUND);

		LLUUID new_asset_id;
		new_asset_id.generate();
		
		src->setAssetUUID(new_asset_id);
		std::string new_desc = "GIS Testing";
		src->setDescription(new_desc);
		
		S32 new_price = rand();
		LLSaleInfo new_sale_info(LLSaleInfo::FS_COPY, new_price);
		src->setSaleInfo(new_sale_info);

		U32 new_flags = rand();
		S32 new_creation = time(NULL);

		LLPermissions new_perm;

		LLUUID new_creator_id;
		new_creator_id.generate();
	
		LLUUID new_owner_id;
		new_owner_id.generate();

		LLUUID last_owner_id;
		last_owner_id.generate();

		LLUUID new_group_id;
		new_group_id.generate();
		new_perm.init(new_creator_id, new_owner_id, last_owner_id, new_group_id);
		new_perm.initMasks(PERM_ALL, PERM_ALL, PERM_COPY, PERM_COPY, PERM_MODIFY | PERM_COPY);
		src->setPermissions(new_perm);

		src->setInventoryType(LLInventoryType::IT_SOUND);
		src->setFlags(new_flags);
		src->setCreationDate(new_creation);

		// test a save/load cycle to LLSD and back again
		LLSD sd = ll_create_sd_from_inventory_item(src);
		LLPointer<LLInventoryItem> dst = new LLInventoryItem;
		bool successful_parse = dst->fromLLSD(sd);
		ensure_equals("0.LLInventoryItem::fromLLSD()", successful_parse, true);

		LLPointer<LLInventoryItem> src1 = create_random_inventory_item();
		src1->copyItem(src);
		
		ensure_equals("1.item id::getUUID() failed", dst->getUUID(), src1->getUUID());
		ensure_equals("2.parent::getParentUUID() failed", dst->getParentUUID(), src1->getParentUUID());
		ensure_equals("3.name::getName() failed", dst->getName(), src1->getName());
		ensure_equals("4.type::getType() failed", dst->getType(), src1->getType());
		
		ensure_equals("5.permissions::getPermissions() failed", dst->getPermissions(), src1->getPermissions());
		ensure_equals("6.description::getDescription() failed", dst->getDescription(), src1->getDescription());
		ensure_equals("7.sale type::getSaleType() failed type", dst->getSaleInfo().getSaleType(), src1->getSaleInfo().getSaleType());
		ensure_equals("8.sale price::getSalePrice() failed price", dst->getSaleInfo().getSalePrice(), src1->getSaleInfo().getSalePrice());
		ensure_equals("9.asset id::getAssetUUID() failed id", dst->getAssetUUID(), src1->getAssetUUID());
		ensure_equals("10.inventory type::getInventoryType() failed type", dst->getInventoryType(), src1->getInventoryType());
		ensure_equals("11.flags::getFlags() failed", dst->getFlags(), src1->getFlags());
		ensure_equals("12.creation::getCreationDate() failed", dst->getCreationDate(), src1->getCreationDate());

		// quick test to make sure generateUUID() really works
		src1->generateUUID();	
		ensure_not_equals("13.item id::generateUUID() failed", src->getUUID(), src1->getUUID());
	}