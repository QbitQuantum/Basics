//*****************************************************************************
//  Function        : FtpOpen
//  Description     : Open & Login
//  Input           : aCfg;           // TCP port info.
//                    aLoginName;     // Login name
//                    aLoginPassword; // password.
//  Return          : 0/-1;       // 0  => Success
//                                // -1 => Error
//  Note            : N/A
//  Globals Changed : N/A
//*****************************************************************************
static int FtpOpen(struct MW_TCP_PORT *aCfg, char *aLoginName, char *aLoginPassword)
{
  int i;

  // Close all
  CloseAll();
  TBuffers.gRxBuf = MallocMW(COMM_BUFF_SIZE); // buffer de recepcion de datos
  TBuffers.gTxBuf = MallocMW(COMM_BUFF_SIZE); // buffer de recepcion de datos
  memset(TBuffers.gRxBuf,0x00,COMM_BUFF_SIZE);
  memset(TBuffers.gTxBuf,0x00,COMM_BUFF_SIZE);
  // Open Port
  graphicWindow("CONEXION FTP");
  DispLineMW("Conectando...",MW_LINE3,MW_CLRDISP|MW_CENTER|MW_BIGFONT);

  FlushAll ();
  if (IOCtlMW(gFtpHandle, IO_FTP_CONNECT, aCfg) == FALSE) {
	  graphicWindow("ERROR");
	  //centerS(3,1,21,"Fallo al intentar");
	  DispLineMW("Fallo al intentar",MW_LINE4,MW_CLRDISP|MW_CENTER|MW_SMFONT);
	  DispLineMW("Abrir!!",MW_LINE5,MW_CLRDISP|MW_CENTER|MW_SMFONT);
//	  centerS(4,1,21,"Abrir!!");
	  Delay10ms(300);
	  FreeMW(TBuffers.gRxBuf);
	  FreeMW(TBuffers.gTxBuf);
    return -1;
  }
  i = WaitCmdResp(TIMEOUT_RESP);
  if (i < 0) {
		graphicWindow("ERROR");
//		centerS(3,1,21,"El tiempo de espera");
//		centerS(4,1,21,"se agoto al");
//		centerS(5,1,21,"intentat abrir!!");
		DispLineMW("El tiempo de espera",MW_LINE3,MW_CLRDISP|MW_CENTER|MW_SMFONT);
		DispLineMW("se agoto al",MW_LINE4,MW_CLRDISP|MW_CENTER|MW_SMFONT);
		DispLineMW("intentat abrir!!",MW_LINE5,MW_CLRDISP|MW_CENTER|MW_SMFONT);
//		getch(300);
		 Delay10ms(300);
		 FreeMW(TBuffers.gTxBuf);
		 FreeMW(TBuffers.gRxBuf);
    return -1;
  }
  if (i >= 400) {
    PrintfMW("\x1B\xE0""Open:%d\x05\x1D", i);
    FreeMW(TBuffers.gRxBuf);
    return -1;
  }

  if (WaitStatus(MW_FTP_STAT_CONNECTED, TIMEOUT_STATUS)<0) {
	  graphicWindow("ERROR");
//	  centerS(3,1,21,"Fallo al intentar");
//	  centerS(4,1,21,"Abrir!!");
//	  getch(300);
	  DispLineMW("Fallo al intentar",MW_LINE4,MW_CLRDISP|MW_CENTER|MW_SMFONT);
	  DispLineMW("Abrir 2!!",MW_LINE5,MW_CLRDISP|MW_CENTER|MW_SMFONT);
	  Delay10ms(300);
	  FreeMW(TBuffers.gRxBuf);FreeMW(TBuffers.gTxBuf);
    return -1;
  }

  // Login
  DispLineMW("Negociando...",MW_LINE4,MW_CLRDISP|MW_CENTER|MW_SMFONT);
  //centerS(4,1,21,"Negociando...");
  FlushAll();
  SprintfMW ((char *)TBuffers.gTxBuf, "LOGIN %s %s", aLoginName, aLoginPassword);
  if (IOCtlMW(gFtpHandle, IO_FTP_CMD_SEND, TBuffers.gTxBuf) == FALSE) {
	  graphicWindow("ERROR");
	  DispLineMW("Fallo al intentar",MW_LINE3,MW_CLRDISP|MW_CENTER|MW_SMFONT);
	  DispLineMW("Login",MW_LINE4,MW_CLRDISP|MW_CENTER|MW_SMFONT);
//	  centerS(3,1,21,"Fallo al intentar");
//	  centerS(4,1,21,"login!!");
//	  getch(300);
	  Delay10ms(300);
	  FreeMW(TBuffers.gRxBuf);FreeMW(TBuffers.gTxBuf);
    return -1;
  }
  i = WaitCmdResp(TIMEOUT_RESP);
  if (i < 0) {
		graphicWindow("ERROR");
//		centerS(3,1,21,"El tiempo de espera");
//		centerS(4,1,21,"se agoto al");
//		centerS(5,1,21,"intentat login!!");
		  DispLineMW("El tiempo de espera",MW_LINE3,MW_CLRDISP|MW_CENTER|MW_SMFONT);
		  DispLineMW("se agoto al",MW_LINE4,MW_CLRDISP|MW_CENTER|MW_SMFONT);
		  DispLineMW("intentat login!!",MW_LINE5,MW_CLRDISP|MW_CENTER|MW_SMFONT);
//		getch(300);
		  Delay10ms(300);
		  FreeMW(TBuffers.gRxBuf);FreeMW(TBuffers.gTxBuf);
    return -1;
  }
  if (i >= 400) {
	  graphicWindow("ERROR");
//	  centerS(3,1,21,"Fallo al intentar");
//	  centerS(4,1,21,"login!!");
//	  getch(300);
	  DispLineMW("Fallo al intentar",MW_LINE3,MW_CLRDISP|MW_CENTER|MW_SMFONT);
	  DispLineMW("login!!",MW_LINE4,MW_CLRDISP|MW_CENTER|MW_SMFONT);
	  Delay10ms(300);
	  FreeMW(TBuffers.gRxBuf);FreeMW(TBuffers.gTxBuf);
    return -1;
  }
  if (WaitStatus(MW_FTP_STAT_OPENED, TIMEOUT_STATUS) < 0) {
	  graphicWindow("ERROR");
//	  centerS(3,1,21,"Fallo al intentar");
//	  centerS(4,1,21,"login!!");
//	  getch(300);
	  DispLineMW("Fallo al intentar",MW_LINE3,MW_CLRDISP|MW_CENTER|MW_SMFONT);
	  DispLineMW("login!!",MW_LINE4,MW_CLRDISP|MW_CENTER|MW_SMFONT);
	  Delay10ms(300);
	  FreeMW(TBuffers.gRxBuf);FreeMW(TBuffers.gTxBuf);
    return -1;
  }
  return 0;
}