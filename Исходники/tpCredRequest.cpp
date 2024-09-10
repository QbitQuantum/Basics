/*
 * Cook up a CSSM_DATA with specified integer, DER style (minimum number of
 * bytes, big-endian).
 */
static void intToDER(
	CSSM_INTPTR theInt,
	CSSM_DATA &DER_Data,
	Allocator &alloc)
{
	/*
 	 * Calculate length in bytes of encoded integer, minimum length of 1. 
	 */
	DER_Data.Length = 1;
	uintptr_t unsignedInt = (uintptr_t)theInt;
	while(unsignedInt > 0xff) {
		DER_Data.Length++;
		unsignedInt >>= 8;
	}

	/*
	 * DER encoding requires top bit to be zero, else it's a negative number. 
	 * Even though we're passing around integers as CSSM_INTPTR, they really are
 	 * always unsigned. 
	 * unsignedInt contains the m.s. byte of theInt in its l.s. byte. 
	 */
	if(unsignedInt & 0x80) {
		DER_Data.Length++;
	}
	
	DER_Data.Data = (uint8 *)alloc.malloc(DER_Data.Length);
	uint8 *dst = DER_Data.Data + DER_Data.Length - 1;
	unsignedInt = (uintptr_t)theInt;
	for(unsigned dex=0; dex<DER_Data.Length; dex++) {
		*dst-- = unsignedInt & 0xff;
		/* this shifts off to zero if we're adding a zero at the top */
		unsignedInt >>= 8;
	}
}