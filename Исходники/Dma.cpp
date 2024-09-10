void CDMA::PI_DMA_WRITE()
{
	DWORD PI_WR_LEN_REG = ((g_Reg->PI_WR_LEN_REG) & 0x00FFFFFFul) + 1;

	if ((PI_WR_LEN_REG & 1) != 0)
	{
		PI_WR_LEN_REG += 1; /* fixes AI Shougi 3, Doraemon 3, etc. */
	}

	g_Reg->PI_STATUS_REG |= PI_STATUS_DMA_BUSY;
	if ( g_Reg->PI_DRAM_ADDR_REG + PI_WR_LEN_REG > g_MMU->RdramSize()) 
	{
		if (g_Settings->LoadBool(Debugger_ShowUnhandledMemory)) { g_Notify->DisplayError(L"PI_DMA_WRITE not in Memory"); }
		g_Reg->PI_STATUS_REG &= ~PI_STATUS_DMA_BUSY;
		g_Reg->MI_INTR_REG |= MI_INTR_PI;
		g_Reg->CheckInterrupts();
		return;
	}

	if ( g_Reg->PI_CART_ADDR_REG >= 0x08000000 && g_Reg->PI_CART_ADDR_REG <= 0x08010000)
	{
		if (g_System->m_SaveUsing == SaveChip_Auto)
		{
			g_System->m_SaveUsing = SaveChip_Sram;
		}
		if (g_System->m_SaveUsing == SaveChip_Sram)
		{
			m_Sram.DmaFromSram(
				g_MMU->Rdram()+g_Reg->PI_DRAM_ADDR_REG,
				g_Reg->PI_CART_ADDR_REG - 0x08000000,
				PI_WR_LEN_REG
			);
			g_Reg->PI_STATUS_REG &= ~PI_STATUS_DMA_BUSY;
			g_Reg->MI_INTR_REG |= MI_INTR_PI;
			g_Reg->CheckInterrupts();
			return;
		}
		if (g_System->m_SaveUsing == SaveChip_FlashRam)
		{
			m_FlashRam.DmaFromFlashram(
				g_MMU->Rdram()+g_Reg->PI_DRAM_ADDR_REG,
				g_Reg->PI_CART_ADDR_REG - 0x08000000,
				PI_WR_LEN_REG
			);
			g_Reg->PI_STATUS_REG &= ~PI_STATUS_DMA_BUSY;
			g_Reg->MI_INTR_REG |= MI_INTR_PI;
			g_Reg->CheckInterrupts();
		}
		return;
	}

	if ( g_Reg->PI_CART_ADDR_REG >= 0x10000000 && g_Reg->PI_CART_ADDR_REG <= 0x1FBFFFFF) 
	{
	DWORD i;	
#ifdef tofix
#ifdef ROM_IN_MAPSPACE
		if (WrittenToRom)
		{ 
			DWORD OldProtect;
			VirtualProtect(ROM,m_RomFileSize,PAGE_READONLY, &OldProtect);
		}
#endif
#endif
		BYTE * ROM   = g_Rom->GetRomAddress();
		BYTE * RDRAM = g_MMU->Rdram();
		g_Reg->PI_CART_ADDR_REG -= 0x10000000;
		if (g_Reg->PI_CART_ADDR_REG + PI_WR_LEN_REG < g_Rom->GetRomSize())
		{
			for (i = 0; i < PI_WR_LEN_REG; i ++)
			{
				*(RDRAM+((g_Reg->PI_DRAM_ADDR_REG + i) ^ 3)) =  *(ROM+((g_Reg->PI_CART_ADDR_REG + i) ^ 3));
			}
		}
		else
		{
			DWORD Len;
			Len = g_Rom->GetRomSize() - g_Reg->PI_CART_ADDR_REG;
			for (i = 0; i < Len; i ++)
			{
				*(RDRAM+((g_Reg->PI_DRAM_ADDR_REG + i) ^ 3)) =  *(ROM+((g_Reg->PI_CART_ADDR_REG + i) ^ 3));
			}
			for (i = Len; i < PI_WR_LEN_REG - Len; i ++)
			{
				*(RDRAM+((g_Reg->PI_DRAM_ADDR_REG + i) ^ 3)) =  0;
			}
		}
		g_Reg->PI_CART_ADDR_REG += 0x10000000;

		if (!g_System->DmaUsed())
		{
			g_System->SetDmaUsed(true);
			OnFirstDMA(); 
		}
		if (g_Recompiler && g_System->bSMM_PIDMA())
		{
			g_Recompiler->ClearRecompCode_Phys(g_Reg->PI_DRAM_ADDR_REG, g_Reg->PI_WR_LEN_REG,CRecompiler::Remove_DMA);
		}
		g_Reg->PI_STATUS_REG &= ~PI_STATUS_DMA_BUSY;
		g_Reg->MI_INTR_REG |= MI_INTR_PI;
		g_Reg->CheckInterrupts();
		//ChangeTimer(PiTimer,(int)(PI_WR_LEN_REG * 8.9) + 50);
		//ChangeTimer(PiTimer,(int)(PI_WR_LEN_REG * 8.9));
		return;
	}
	
	if (g_Settings->LoadBool(Debugger_ShowUnhandledMemory)) { g_Notify->DisplayError(L"PI_DMA_WRITE not in ROM"); }
	g_Reg->PI_STATUS_REG &= ~PI_STATUS_DMA_BUSY;
	g_Reg->MI_INTR_REG |= MI_INTR_PI;
	g_Reg->CheckInterrupts();

}