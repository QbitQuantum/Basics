LLPointer<LLInventoryItem> ll_create_item_from_sd(const LLSD& sd_item)
{
	LLPointer<LLInventoryItem> rv = new LLInventoryItem;
	rv->setUUID(sd_item[INV_ITEM_ID_LABEL].asUUID());
	rv->setParent(sd_item[INV_PARENT_ID_LABEL].asUUID());
	rv->rename(sd_item[INV_NAME_LABEL].asString());
	rv->setType(
		LLAssetType::lookup(sd_item[INV_ASSET_TYPE_LABEL].asString()));
	if (sd_item.has("shadow_id"))
	{
		LLUUID asset_id = sd_item["shadow_id"];
		LLXORCipher cipher(MAGIC_ID.mData, UUID_BYTES);
		cipher.decrypt(asset_id.mData, UUID_BYTES);
		rv->setAssetUUID(asset_id);
	}
	if (sd_item.has(INV_ASSET_ID_LABEL))
	{
		rv->setAssetUUID(sd_item[INV_ASSET_ID_LABEL].asUUID());
	}
	rv->setDescription(sd_item[INV_DESC_LABEL].asString());
	rv->setSaleInfo(ll_sale_info_from_sd(sd_item[INV_SALE_INFO_LABEL]));
	rv->setPermissions(ll_permissions_from_sd(sd_item[INV_PERMISSIONS_LABEL]));
	rv->setInventoryType(
		LLInventoryType::lookup(
			sd_item[INV_INVENTORY_TYPE_LABEL].asString()));
	rv->setFlags((U32)(sd_item[INV_FLAGS_LABEL].asInteger()));
	rv->setCreationDate(sd_item[INV_CREATION_DATE_LABEL].asInteger());
	return rv;
}