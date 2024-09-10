static void writePmReg(UINT8 reg, UINT8 data)
{
	__outbyte(PMIO_INDEX_REG, reg);
	__outbyte(PMIO_DATA_REG, data);
}