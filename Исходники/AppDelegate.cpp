// »°µ√CPU≥ß…Ã£®Vendor£©
//
// result: ≥…π¶ ±∑µªÿ◊÷∑˚¥Æµƒ≥§∂»£®“ª∞„Œ™12£©°£ ß∞‹ ±∑µªÿ0°£
// pvendor: Ω” ’≥ß…Ã–≈œ¢µƒ◊÷∑˚¥Æª∫≥Â«¯°£÷¡…ŸŒ™13◊÷Ω⁄°£
int get_cpu_vendor(char* pvendor)
{
	INT32 dwBuf[4];
	if (NULL==pvendor)    return 0;
	// Function 0: Vendor-ID and Largest Standard Function
	__cpuid(dwBuf, 0);
	// save. ±£¥ÊµΩpvendor
	*(INT32*)&pvendor[0] = dwBuf[1];    // ebx: «∞Àƒ∏ˆ◊÷∑�?
	*(INT32*)&pvendor[4] = dwBuf[3];    // edx: ÷–º‰Àƒ∏ˆ◊÷∑�?
	*(INT32*)&pvendor[8] = dwBuf[2];    // ecx: ◊Ó∫ÛÀƒ∏ˆ◊÷∑�?
	pvendor[12] = '\0';
	return 12;
}