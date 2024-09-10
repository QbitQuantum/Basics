// Get information about the SD card and interface speed
MassStorage::InfoResult MassStorage::GetCardInfo(size_t slot, uint64_t& capacity, uint64_t& freeSpace, uint32_t& speed, uint32_t& clSize)
{
	if (slot >= NumSdCards)
	{
		return InfoResult::badSlot;
	}

	SdCardInfo& inf = info[slot];
	if (!inf.isMounted)
	{
		return InfoResult::noCard;
	}

	capacity = (uint64_t)sd_mmc_get_capacity(slot) * 1024;
	speed = sd_mmc_get_interface_speed(slot);
	String<ShortScratchStringLength> path;
	path.printf("%u:/", slot);
	uint32_t freeClusters;
	FATFS *fs;
	const FRESULT fr = f_getfree(path.c_str(), &freeClusters, &fs);
	if (fr == FR_OK)
	{
		clSize = fs->csize * 512;
		freeSpace = (fr == FR_OK) ? (uint64_t)freeClusters * clSize : 0;
	}
	else
	{
		clSize = 0;
		freeSpace = 0;
	}
	return InfoResult::ok;
}