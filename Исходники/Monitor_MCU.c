//=============================================================================
//			Help Message
//=============================================================================
void MCUHelp(void)
{

	Puts("\n=======================================================");
	Puts("\n>>>     Welcome to Intersil Monitor  Rev 1.00     <<<");
	Puts("\n=======================================================");
	Puts("\n   MCU Rs ii             ; Read SFR");
	Puts("\n   MCU Ws ii dd          ; Write SFR");
	Puts("\n   MCU Ds                ; Dump SFR");
	Puts("\n   MCU Bs ii se dd       ; bitwise SFR. s:start bit, e:end bit");
	Puts("\n   MCU sfr               ; Dump SFR map");
	Puts("\n   MCU Rx ii             ; Read XDATA");
	Puts("\n   MCU Wx ii dd          ; Write XDATA");
	Puts("\n   MCU Dx [ii] [cc]      ; Dump XDATA");
#if defined(SUPPORT_WATCHDOG) || defined(DEBUG_WATCHDOG)
	Puts("\n   MCU WDT [0/1/2]       ; WatchDog disable/enable/test");
#endif
	Puts("\n   MCU stop              ; stop mode");
	Puts("\n   MCU IE n              ; enable interrupt");
	Puts("\n   MCU DE n              ; disable interrupt");
	Puts("\n   MCU EI [n]            ; extended interrupt");
	Puts("\n   MCU INT               ; help interrupt");
	Puts("\n");

}