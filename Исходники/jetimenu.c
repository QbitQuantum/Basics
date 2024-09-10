// -----------------------------------------------------------
// the menu functions
// -----------------------------------------------------------
void Menu_Status(uint8_t key)
{						//0123456789ABCDEF
#if !defined (RECEIVER_SPEKTRUM_DX7EXP) && !defined (RECEIVER_SPEKTRUM_DX8EXP)
	JetiBox_printfxy(0,0,"%2i.%1iV",UBat/10, UBat%10);
	if(NaviDataOkay)
	{
		JetiBox_printfxy(6,0,"%3d%c %03dm%c",ErsatzKompassInGrad, 0xDF, GPSInfo.HomeDistance/10,NC_GPS_ModeCharacter);
	}
	else
	{
		JetiBox_printfxy(6,0,"Status");
	}

#if (defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__))
	if(NC_ErrorCode) 
	{
	 static unsigned int timer;
	 static char toggle = 1;
     
	 if(CheckDelay(timer)) { if(toggle) toggle = 0; else toggle = 1; timer = SetDelay(1500);};
     if(toggle)
	  {
       LIBFC_JetiBox_SetPos(0);
 	   _printf_P(&LIBFC_JetiBox_Putchar, NC_ERROR_TEXT[NC_ErrorCode] , 0); 
	  } 
	  else 
	  {
	   JetiBox_printfxy(6,0,"ERROR: %2d ",NC_ErrorCode);
//	   if(MotorenEin) JetiBeep = 'O'; 
	  } 
	}
	else 
	if(ShowSettingNameTime)
	{
	 LIBFC_JetiBox_Clear();
	 JetiBox_printfxy(0,1,"Set%d:%s  ",ActiveParamSet,EE_Parameter.Name); 
	 return; // nichts weiter ausgeben
	}

#else
	if(NC_ErrorCode) { JetiBox_printfxy(6,0,"ERROR: %2d ",NC_ErrorCode); if(MotorenEin) JetiBeep = 'S';}; 
#endif
	JetiBox_printfxy(0,1,"%4i %2i:%02i",Capacity.UsedCapacity,FlugSekunden/60,FlugSekunden%60);
	if(Parameter_GlobalConfig & CFG_HOEHENREGELUNG)
	{
		JetiBox_printfxy(10,1,"%4im%c", (int16_t)(HoehenWert/100),VarioCharacter);
	}
#endif
}