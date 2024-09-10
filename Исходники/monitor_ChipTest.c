void ChipTest_Register_RW(BYTE page)
{
	BYTE *pDefData, *pWMask, *pRMask, Mask;
	BYTE i,j,Index;
	WORD PageIndex;
	BYTE prev_data;
	volatile BYTE value;

	//link data
	switch(page) {
	case 0: pDefData = DefPage0Regs; pWMask = RegMask_W_Page0; pRMask = RegMask_R_Page0;	break;
	case 1: pDefData = DefPage1Regs; pWMask = RegMask_W_Page1; pRMask = RegMask_R_Page1;	break;
	case 2: pDefData = DefPage2Regs; pWMask = RegMask_W_Page2; pRMask = RegMask_R_Page2;	break;
	case 3: pDefData = DefPage3Regs; pWMask = RegMask_W_Page3; pRMask = RegMask_R_Page3;	break;
	case 4: pDefData = DefPage4Regs; pWMask = RegMask_W_Page4; pRMask = RegMask_R_Page4;	break;
	case 5: pDefData = DefPage5Regs; pWMask = RegMask_W_Page5; pRMask = RegMask_R_Page5;	break;
	}
	Printf("\nPage:%bd================", page);
	for(i=0; i < 16; i++ ) {
		for(j=0; j < 16; j++) {
			//default value check
			Index = i*16+j;
			PageIndex = ((WORD)page << 8) + Index;
			Mask = pWMask[Index] | pRMask[Index];
			if(pWMask[Index]) {
				Printf("\nREG%01bx%02bx WMask:%02bx RMask:%02bx Def:%02bx",page, Index, pWMask[Index], pRMask[Index], pDefData[Index]);

				value = ReadTW88(PageIndex);
	
				if((value & Mask) != (pDefData[Index] & Mask)) {
					Printf(" Read:%02bx", value);
				}
			}
			else if(pRMask[Index]) {
				//read only.
				Printf("\nREG%01bx%02bx WMask:%02bx RMask:%02bx Def:__",page, Index, pWMask[Index], pRMask[Index]);

				value = ReadTW88(PageIndex);
				Printf(" Read:%02bx", value);
			}
			else if(pDefData[Index]==0xBF) {
				value = ReadTW88(PageIndex);
				if(value != 0xBF) {
					Printf("\nREG%01bx%02bx BF. Read:%02bx", page, Index, value);

					WriteTW88(PageIndex, 0xFF);
					value = ReadTW88(PageIndex);
					if(value != 00) {
						Printf("\nREG%01bx%02bx BF. but writable.", page, Index);
					}
				}
				else {
					//assume NO register.
				}
			}

			//skip
			if(PageIndex == REG4E1)	{ //it is a clock
				Puts("->skip");
				continue;
			}

			//write test
			if(pWMask[Index]) {
				prev_data = ReadTW88(PageIndex);

				WriteTW88(PageIndex, 0x00);
				value = ReadTW88(PageIndex);
				if(value != 0x00) {
					//Printf(" REG%01bx%02bx W:00 R:%02bx", page,Index,value);
					Printf(" W:00_R:%02bx", value);
				}
				WriteTW88(PageIndex, 0xFF & pWMask[Index]);
				value = ReadTW88(PageIndex);
				if((value & pWMask[Index]) != (0xFF & pWMask[Index])) {
					//Printf(" REG%01bx%02bx W:%02bx R:%02bx", page,Index, pWMask[Index], value);
					Printf(" W:%02bx_R:%02bx", pWMask[Index], value);
				}
				WriteTW88(PageIndex,prev_data);
			}
		}
	} 
}