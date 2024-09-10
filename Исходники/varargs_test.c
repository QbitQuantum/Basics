word64 fn00000001400012BC(word32 edx, word64 rdi, word64 r13, selector gs, word64 qwArg08, word64 qwArg10)
{
	if (fn0000000140001600(0x01, edx, r13) == 0x00)
	{
		word64 rcx_362;
		byte bl_363;
		fn0000000140001974(0x07, qwLoc04, qwArg00, qwArg04, qwArg0C, out rcx_362, out bl_363);
		int3();
	}
	Mem23[fp - 0x14 + 0x00:byte] = 0x00;
	word32 eax_25 = fn00000001400015C4(gs);
	word64 rax_28 = DPB(rax, eax_25, 0);
	byte bl_29 = (byte) eax_25;
	word32 ecx_33 = Mem23[0x00000001400035B0 + 0x00:word32];
	if (ecx_33 == 0x01)
	{
		ecx_33 = 0x07;
		word64 rcx_355;
		rax_28 = DPB(rax, fn0000000140001974(0x07, qwLoc04, qwArg00, qwArg04, qwArg0C, out rcx_355, out bl_29), 0);
	}
	word64 rax_233;
	if (ecx_33 == 0x00)
	{
		Mem331[0x00000001400035B0 + 0x00:word32] = 0x01;
		word64 rax_334 = DPB(rax_28, _initterm_e(0x00000001400021B8, 0x00000001400021D0), 0);
		if (_initterm_e(0x00000001400021B8, 0x00000001400021D0) != 0x00)
		{
			rax_233 = DPB(rax_28, 0xFF, 0);
			return rax_233;
		}
		_initterm(0x00000001400021A0, 0x00000001400021B0);
		Mem344[0x00000001400035B0 + 0x00:word32] = 0x02;
	}