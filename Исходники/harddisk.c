void readHardSector(u32 sector, u8 *buffer, int sectorCount)
{
  	command.features = 0;
	command.count = sectorCount;
	command.lbaLow	= sector & 0xFF;
	command.lbaMid	= (sector >>  8) & 0xFF;
	command.lbaHigh	= (sector >> 16) & 0xFF;

	command.device = MAKE_DEVICE_REG(1, 0, (sector >> 24) & 0xF);
	command.command = ATA_READ;
	
	isHardDiskReady = FALSE;
	sendHdCommand(&command);
	int sectorLeft = command.count;
	while (sectorLeft>0) {
		waitForStatus(STATUS_BSY, 0, HD_TIMEOUT);
		readPort(REG_DATA, buffer, 512);
		buffer+=512;
		sectorLeft--;
	}
}