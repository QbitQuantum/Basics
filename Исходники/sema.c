static int smb_write_blk(u8 slave, u8 command, u8 length, const u8 *data)
{
	__outbyte(SMB0_STATUS, 0x1E);		// clear error status
	__outbyte(SMB0_ADDRESS, slave & ~1);	// slave addr + direction = out
	__outbyte(SMB0_HOSTCMD, command);	// or destination offset
	__outbyte(SMB0_DATA0, length);		// sent before data
	__inbyte(SMB0_CONTROL);			// reset block data array
	while (length--)
		__outbyte(SMB0_BLOCKDATA, *(data++));
	__outbyte(SMB0_CONTROL, 0x54);		// execute block write, no IRQ

	while (__inbyte(SMB0_STATUS) == 0x01);	// busy, no errors
	return __inbyte(SMB0_STATUS) ^ 0x02;	// 0x02 = completed, no errors
}