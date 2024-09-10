static void writePmReg (int reg, int data)
{
	__outbyte (0xCD6, reg);
	__outbyte (0xCD7, data);
}