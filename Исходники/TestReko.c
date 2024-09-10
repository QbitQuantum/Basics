void fn0040127B(word32 ebx, word32 esi, word32 edi)
{
	fn00401561();
	Eq_5 * ebp_10 = fn00401770(ebx, esi, edi, dwLoc0C, 4202984, 0x0C);
	ebp_10->dw0000 = 0;
	Eq_25 * esp_105 = fp - 8;
	word32 edx_17 = fs->ptr0018->dw0004;
	word32 edi_18 = 0;
	do
	{
		__lock();
		word32 eax_24;
		__cmpxchg(globals->dw403368, edx_17, 0, out eax_24);
		if (eax_24 == 0)
			goto l00401151;
	} while (eax_24 != edx_17);
	edi_18 = 1;
l00401151:
	if (globals->dw40336C == 1)
	{
		Mem185[fp - 0x0C:word32] = 31;
		_amsg_exit();
		esp_105 = fp + 0xFFFFFFF4;
l0040119D:
		if (globals->dw40336C == 1)
		{
			Eq_25 * esp_174 = esp_105 - 4;
			esp_174->dw0000 = 4202652;
			esp_174->dw0000 = 4202644;
			_initterm();
			globals->dw40336C = 2;
			esp_105 = esp_174;
		}
		if (edi_18 == 0)
			globals->dw403368 = 0;
		if (globals->ptr403378 != null)
		{
			Eq_167 * esp_152 = esp_105 - 4;
			esp_152->dw0000 = 4207480;
			word32 eax_154 = fn00401470(dwArg00);
			esp_105 = esp_152 + 4;
			if (eax_154 != 0)
			{
				esp_152->dw0000 = 0;
				esp_152->t0004.dw0000 = 2;
				esp_152->t0004.dw0000 = 0;
				esp_105 = esp_152 - 8;
				Mem165[4207480:word32]();
			}