static void
cmos_set(unsigned i, unsigned d) {
	_disable();
	chip_write8(0,i);
	chip_write8(1,d);
	_enable();	
}