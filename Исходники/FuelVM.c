void fn00401000(word32 edx, word32 dwArg04, word32 dwArg08, word32 dwArg0C)
{
	globals->t403180 = GetModuleHandleA(null);
	DialogBoxParamA(globals->t403180, (CHAR) 0x000003EC, null, &globals->ptr40102C, 0x00000000);
	ExitProcess(0x00000000);
	if (dwArg08 == 0x00000110)
	{
		Mem53[fp - 0x00000008:word32] = 0x00000053;
		Mem55[fp - 0x0000000C:word32] = 0x00000000;
		Mem57[fp - 0x00000010:word32] = 0x00000000;
		SetWindowPos(dwArg04, null, 0x00000000, 0x00000000, 0x000003EC, 0x00000000, 0x0040102C);
		Mem70[fp - 0x00000008:word32] = 0x000007D1;
		Mem72[fp - 0x0000000C:word32] = Mem70[0x00403180:word32];
		Mem76[fp - 0x00000008:word32] = LoadBitmapA(0x00000000, 0x0040102C);
		globals->t403194 = CreatePatternBrush(0x0040102C);
		Mem81[fp - 0x00000008:word32] = 0x0000000A;
		Mem83[fp - 0x0000000C:word32] = 0x000007D2;
		Mem85[fp - 0x00000010:word32] = Mem83[0x00403180:word32];
		globals->t403184 = FindResourceA(() 0x000003EC, 0x00000000, 0x0040102C);
		Mem90[fp - 0x00000008:word32] = Mem88[0x00403184:word32];
		Mem92[fp - 0x0000000C:word32] = Mem90[0x00403180:word32];
		globals->t403188 = LoadResource(0x00000000, 0x0040102C);
		Mem97[fp - 0x00000008:word32] = Mem95[0x00403184:word32];
		Mem99[fp - 0x0000000C:word32] = Mem97[0x00403180:word32];
		globals->t403190 = SizeofResource(0x00000000, 0x0040102C);
		Mem104[fp - 0x00000008:word32] = Mem102[0x00403188:word32];
		globals->t40318C = LockResource(0x0040102C);
		Mem109[fp - 0x00000008:word32] = Mem107[0x0040318C:word32];
		Mem111[fp - 0x0000000C:word32] = Mem109[0x00403190:word32];
		Mem113[fp - 0x00000010:word32] = 0x00000000;
		Eq_6 eax_114 = ExtCreateRegion(() 0x000003EC, 0x00000000, 0x0040102C);
		Mem117[fp - 0x00000008:word32] = 0x00000001;
		Mem119[fp - 0x0000000C:word32] = eax_114;
		Mem121[fp - 0x00000010:word32] = dwArg04;
		SetWindowRgn(() 0x000003EC, 0x00000000, 0x0040102C);
		Mem125[fp - 0x00000008:word32] = 0x00000001;
		Mem127[fp - 0x0000000C:word32] = dwArg04;
		ShowWindow(0x00000000, 0x0040102C);
l004011BC:
		return;
	}