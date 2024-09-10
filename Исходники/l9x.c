static uint8_t getb(uint8_t *p)
{
	uint16_t addr = (uint16_t)p;
	uint8_t ah = addr >> 8;
	uint8_t c;

	if (ah == last_ah) {
		STAT(fast);
		return last_base[addr&0xff];
	}

	/* Find the right buffer */
	c = page_find(ah);
	last_ah = ah;
	last_base = page_cache[c];
	return last_base[addr & 0xff];
}