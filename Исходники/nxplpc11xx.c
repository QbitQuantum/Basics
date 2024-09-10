void SysCLK_config_clock_select(uint32 CLKSRC)
{
	
	uint8 i;
	/*執行以下代碼選擇外部12M晶振作為時鐘源*/
	SYSCON->PDRUNCFG     &= ~(1 << 5);          //系統振蕩器上電   
  SYSCON->SYSOSCCTRL    = 0x00000000;			//振蕩器未被旁路，1~20Mhz頻率輸入
  for (i = 0; i < 200; i++) __nop();		    //等待振蕩器穩定
	SYSCON->SYSPLLCLKSEL  = CLKSRC;         	//PLL時鐘源選擇“系統振蕩器” 01, 
																						//IRC: 00 (default).
  SYSCON->SYSPLLCLKUEN  = 0x01;               //更新PLL選擇時鐘源
  SYSCON->SYSPLLCLKUEN  = 0x00;               //先寫0，再寫1達到更新時鐘源的目的（數據手冊規定）
  SYSCON->SYSPLLCLKUEN  = 0x01;
  
	while (!(SYSCON->SYSPLLCLKUEN & 0x01));     //確定時鐘源更新后向下執行
	
	/*執行以下代碼倍頻為48MHz*/
	SYSCON->SYSPLLCTRL    = 0x00000023;     	//設置M=4;P=2; FCLKOUT=12*4=48Mhz
  SYSCON->PDRUNCFG     &= ~(1 << 7);          //PLL上電
  while (!(SYSCON->SYSPLLSTAT & 0x01));	    //確定PLL鎖定以后向下執行
	/*主時鐘源選擇倍頻以后的時鐘*/
	SYSCON->MAINCLKSEL    = 0x00000003;			//主時鐘源選擇PLL后的時鐘
	SYSCON->MAINCLKUEN    = 0x01;				//更新主時鐘源
	SYSCON->MAINCLKUEN    = 0x00;				//先寫0，再寫1達到更新時鐘源的目的（數據手冊規定）
	SYSCON->MAINCLKUEN    = 0x01;
	
	while (!(SYSCON->MAINCLKUEN & 0x01));	    //確定主時鐘鎖定以后向下執行

	SYSCON->SYSAHBCLKDIV  = 0x01;				//AHB時鐘分頻值為1，使AHB時鐘設置為48Mhz
	SYSCON->SYSAHBCLKCTRL |= (1<<6);            //使能GPIO時鐘（用單片機好像沒有不用GPIO的時候）
}