int WINAPI Config(void)
{
	InitDialogItem InitItems[]=
	{
		{DI_DOUBLEBOX, 3, 1,72,21, 0,0,0,0, FMSG(MConfigTitle)},
		{DI_CHECKBOX,5, 2,0,0,0, 0,0,0,  FMSG(MConfigAddToDisksMenu)},      //Add to Disks menu
		{DI_FIXEDIT,35, 2,37, 2,0,0,0,0,NULL},
		{DI_CHECKBOX,5, 3,0,0,0, 0,0,0,  FMSG(MConfigAddToPluginsMenu)},    //Add to Plugins menu
		{DI_TEXT,9, 4,0,0,0, 0,0,0,  FMSG(MHostsMode)},                 //Hosts panel mode
		{DI_FIXEDIT,5, 4, 7, 4,0,0,0,0,NULL},
		{DI_CHECKBOX,5, 5,0,0,0,  0,0,0, FMSG(MConfigReadDiz)},             //Read descriptions
		{DI_CHECKBOX,5, 6,0,0,0, 0,0,0,  FMSG(MConfigUpdateDiz)},           //Update descriptions
		{DI_CHECKBOX,5, 7,0,0,0, 0,0,0,  FMSG(MConfigUploadLowCase)},       //Upload upper in lowercase
		{DI_CHECKBOX,5, 8,0,0,0, 0,0,0,  FMSG(MConfigUploadDialog)},        //Show upload options dialog
		{DI_CHECKBOX,5, 9,0,0,0, 0,0,0,  FMSG(MConfigDefaultResume)},       //Default button is 'Resume'
		{DI_CHECKBOX,5,10,0,0,0, 0,0,0,  FMSG(MAskAbort)},                  //Confirm abort
		{DI_CHECKBOX,5,11,0,0,0, 0,0,0,  FMSG(MShowIdle)},                  //Show idle
		{DI_BUTTON,21,11,0,0,0, 0,0,0,  FMSG(MColor)},                    //Color
		{DI_RADIOBUTTON,32,11,0,0,0,0,DIF_GROUP, 0,  FMSG(MScreen)},                   //( ) 1.Screen
		{DI_RADIOBUTTON,44,11,0,0,0,  0,0,0, FMSG(MCaption)},                  //( ) 2.Caption
		{DI_RADIOBUTTON,58,11,0,0,0,  0,0,0, FMSG(MBoth)},                     //( ) 3.Both

		{DI_CHECKBOX,40, 2,0,0,0, 0,0,0,  FMSG(MKeepAlive)},                //Keepalive packet
		{DI_EDIT,67, 2,70, 2,0,0,0,0,NULL},
		{DI_TEXT,71, 2,0,0,0, 0,0,0,  FMSG(MSec)},                      //s
		{DI_CHECKBOX,40, 3,0,0,0, 0,0,0,  FMSG(MAutoRetry)},                //AutoRetry
		{DI_EDIT,67, 3,70, 3,0,0,0,0,NULL},
		{DI_CHECKBOX,40, 4,0,0,0, 0,0,0,  FMSG(MLongOp)},                   //Long operation beep
		{DI_EDIT,67, 4,70, 4,0,0,0,0,NULL},
		{DI_TEXT,71, 4,0,0,0,  0,0,0, FMSG(MSec)},                      //s
		{DI_TEXT,40, 5,0,0,0, 0,0,0,  FMSG(MWaitTimeout)},              //Server reply timeout (s)
		{DI_EDIT,67, 5,70, 5,0,0,0,0,NULL},
		{DI_CHECKBOX,40, 6,0,0,0, 0,0,0,  FMSG(MDigitDelimit)},             //Digits grouping symbol
		{DI_EDIT,69, 6,70, 6,0,0,0,0,NULL},
		{DI_CHECKBOX,40, 7,0,0,0, 0,0,0,  FMSG(MExtWindow)},                //Show FTP command log
		{DI_TEXT,40, 8,0,0,0,  0,0,0, FMSG(MExtSize)},                  //Log window size
		{DI_EDIT,60, 8,63, 8,0,0,0,0,NULL},
		{DI_TEXT,64, 8,0,0,0,0,0,0,   " x "},
		{DI_EDIT,67, 8,70, 8,0,0,0,0,NULL},
		{DI_TEXT,40, 9,0,0,0,  0,0,0, FMSG(MHostIOSize)},               //I/O buffer size
		{DI_EDIT,60, 9,70, 9,0,0,0,0,NULL},
		{DI_TEXT,40,10,0,0,0,  0,0,0, FMSG(MSilentText)},               //Alert text
		{DI_BUTTON,60,10,0,0,0,0,0,0,   FMSG(MColor)},

		{DI_TEXT,5,12,5,12,0,0,DIF_BOXCOLOR|DIF_SEPARATOR,0,NULL },

		{DI_TEXT,5,13,0,0,0, 0,0,0,  FMSG(MConfigDizNames)},            //Dis names
		{DI_EDIT,5,14,70,14,0,0,0,0,NULL},
		{DI_TEXT,5,15,0,0,0, 0,0,0,  FMSG(MConfigDefPassword)},         //Def pass
		{DI_PSWEDIT,5,16,34,16,0,0,0,0,NULL},
		{DI_TEXT,5,17,0,0,0, 0,0,0,  FMSG(MConfigFirewall)},            //Firewall
		{DI_EDIT,5,18,34,18,0,0,0,0,NULL},
		{DI_TEXT,40,15,0,0,0, 0,0,0,  FMSG(MLogFilename)},              //Log filename
		{DI_EDIT,66,15,70,15,0,0,0,0,NULL},
		{DI_TEXT,71,15,0,0,0, 0,0,0,  FMSG(MKBytes)},
		{DI_EDIT,40,16,70,16,0,0,0,0,NULL},
		{DI_CHECKBOX,40,17,0,0,0,  0,0,0, FMSG(MLogDir)},                   //Log DIR contents
		{DI_CHECKBOX,40,18,0,0,0, 0,0,0,  FMSG(MConfigPassiveMode)},
		{DI_TEXT,5,19,5,19,0,0,DIF_BOXCOLOR|DIF_SEPARATOR,0,NULL },
		{DI_BUTTON,0,20,0,0,0,0,DIF_CENTERGROUP, 1,  FMSG(MOk)},
		{DI_BUTTON,0,20,0,0,0,0,DIF_CENTERGROUP, 0,  FMSG(MCancel)},
		{DI_BUTTON,0,20,0,0,0,0,DIF_CENTERGROUP, 0,  FMSG(MExtOpt)},
	};
#define CFG_ADDDISK       1
#define CFG_DIGIT         2
#define CFG_ADDPLUGINS    3
#define CFG_HOSTMODE      5
#define CFG_READDIZ       6
#define CFG_UPDDIZ        7
#define CFG_UPCASE        8
#define CFG_SHOWUP        9
#define CFG_RESDEF        10
#define CFG_ASKABORT      11
#define CFG_SHOWIDLE      12
#define CFG_IDLECOLOR     13
#define CFG_IDLE_SCREEN   14
#define CFG_IDLE_CAPTION  15
#define CFG_IDLE_BOTH     16
#define CFG_KEEPALIVE     17
#define CFG_KEEPTIME      18
#define CFG_AUTOR         20
#define CFG_AUTORTIME     21
#define CFG_LONGOP        22
#define CFG_LONGOPTIME    23
#define CFG_WAITTIMEOUT   26
#define CFG_DIGDEL        27
#define CFG_DIGCHAR       28
#define CFG_EXT           29
#define CFG_EXT_W         31
#define CFG_EXT_H         33
#define CFG_BUFFSIZE      35
#define CFG_SILENT        37
#define CFG_DESC          40
#define CFG_PASS          42
#define CFG_FIRE          44
#define CFG_LOGLIMIT      46
#define CFG_LOGFILE       48
#define CFG_LOGDIR        49
#define CFG_PASV          50
#define CFG_OK            52
#define CFG_CANCEL        53
#define CFG_EXTBTN        54
	FarDialogItem DialogItems[ARRAYSIZE(InitItems)];
	int           IdleColor    = Opt.IdleColor,
	              ProcessColor = Opt.ProcessColor;
	int           rc;
	InitDialogItems(InitItems,DialogItems,ARRAYSIZE(DialogItems));
	DialogItems[CFG_ADDDISK].Selected = Opt.AddToDisksMenu;
	sprintf(DialogItems[CFG_DIGIT].Data,"%d",Opt.DisksMenuDigit);
	DialogItems[CFG_ADDPLUGINS].Selected  = Opt.AddToPluginsMenu;
	sprintf(DialogItems[CFG_HOSTMODE].Data,"%d",Opt.PluginColumnMode);
	DialogItems[CFG_READDIZ].Selected     = Opt.ReadDescriptions;
	DialogItems[CFG_UPDDIZ].Selected      = Opt.UpdateDescriptions;
	DialogItems[CFG_UPCASE].Selected      = Opt.UploadLowCase;
	DialogItems[CFG_SHOWUP].Selected      = Opt.ShowUploadDialog;
	DialogItems[CFG_RESDEF].Selected      = Opt.ResumeDefault;
	sprintf(DialogItems[CFG_WAITTIMEOUT].Data,"%d",Opt.WaitTimeout);
	DialogItems[CFG_SHOWIDLE].Selected    = Opt.ShowIdle;
	DialogItems[CFG_IDLE_SCREEN].Selected  = Opt.IdleMode == IDLE_CONSOLE;
	DialogItems[CFG_IDLE_CAPTION].Selected = Opt.IdleMode == IDLE_CAPTION;
	DialogItems[CFG_IDLE_BOTH].Selected    = Opt.IdleMode == (IDLE_CONSOLE|IDLE_CAPTION);
	DialogItems[CFG_KEEPALIVE].Selected   = Opt.KeepAlive != 0;
	sprintf(DialogItems[CFG_KEEPTIME].Data,"%d",Opt.KeepAlive);
	DialogItems[CFG_AUTOR].Selected       = Opt.TimeoutRetry;
	sprintf(DialogItems[CFG_AUTORTIME].Data,"%d",Opt.RetryCount);
	DialogItems[CFG_LONGOP].Selected      = Opt.LongBeepTimeout != 0;
	sprintf(DialogItems[CFG_LONGOPTIME].Data,"%d",Opt.LongBeepTimeout);
	DialogItems[CFG_ASKABORT].Selected    = Opt.AskAbort;
	DialogItems[CFG_DIGDEL].Selected      = Opt.dDelimit;
	sprintf(DialogItems[CFG_DIGCHAR].Data,"%c",Opt.dDelimiter);
	DialogItems[CFG_EXT].Selected         = Opt.ExtCmdView;
	sprintf(DialogItems[CFG_EXT_W].Data,"%d",Opt.CmdLine);
	sprintf(DialogItems[CFG_EXT_H].Data,"%d",Opt.CmdLength);
	Size2Str(DialogItems[CFG_BUFFSIZE].Data,Opt.IOBuffSize);
	strcpy(DialogItems[CFG_DESC].Data,Opt.DescriptionNames);
	strcpy(DialogItems[CFG_PASS].Data,Opt.DefaultPassword);
	strcpy(DialogItems[CFG_FIRE].Data,Opt.Firewall);
	sprintf(DialogItems[CFG_LOGLIMIT].Data,"%d",Opt.CmdLogLimit);
	sprintf(DialogItems[CFG_LOGFILE].Data,"%s",Opt.CmdLogFile);
	DialogItems[CFG_LOGDIR].Selected      = Opt.LogOutput;
	DialogItems[CFG_PASV].Selected        = Opt.PassiveMode;

	do
	{
		rc = FDialog(76,23,"Config",DialogItems,ARRAYSIZE(DialogItems));

		if(rc == CFG_OK)
			break;

		if(rc == -1 || rc == CFG_CANCEL)
			return FALSE;

		if(rc == CFG_IDLECOLOR)
			IdleColor = FP_GetColorDialog(IdleColor,&ColorLangs,NULL);
		else if(rc == CFG_SILENT)
			ProcessColor = FP_GetColorDialog(ProcessColor,&ColorLangs,NULL);
		else if(rc == CFG_EXTBTN)
			ExtendedConfig();
	}
	while(true);

//Set to OPT
	Opt.IdleColor          = IdleColor;
	Opt.ProcessColor       = ProcessColor;
	Opt.AddToDisksMenu     = DialogItems[CFG_ADDDISK].Selected;
	Opt.DisksMenuDigit     = atoi(DialogItems[CFG_DIGIT].Data);
	Opt.AddToPluginsMenu   = DialogItems[CFG_ADDPLUGINS].Selected;
	Opt.PluginColumnMode   = atoi(DialogItems[CFG_HOSTMODE].Data);
	Opt.ReadDescriptions   = DialogItems[CFG_READDIZ].Selected;
	Opt.UpdateDescriptions = DialogItems[CFG_UPDDIZ].Selected;
	Opt.UploadLowCase      = DialogItems[CFG_UPCASE].Selected;
	Opt.ShowUploadDialog   = DialogItems[CFG_SHOWUP].Selected;
	Opt.ResumeDefault      = DialogItems[CFG_RESDEF].Selected;
	Opt.WaitTimeout        = atoi(DialogItems[CFG_WAITTIMEOUT].Data);
	Opt.ShowIdle           = DialogItems[CFG_SHOWIDLE].Selected;

	if(DialogItems[CFG_IDLE_SCREEN].Selected)  Opt.IdleMode = IDLE_CONSOLE;
	else if(DialogItems[CFG_IDLE_CAPTION].Selected) Opt.IdleMode = IDLE_CAPTION;
	else
		Opt.IdleMode = IDLE_CONSOLE | IDLE_CAPTION;

	if(DialogItems[CFG_KEEPALIVE].Selected)
		Opt.KeepAlive = atoi(DialogItems[CFG_KEEPTIME].Data);
	else
		Opt.KeepAlive = 0;

	Opt.TimeoutRetry = DialogItems[CFG_AUTOR].Selected;
	Opt.RetryCount   = atoi(DialogItems[CFG_AUTORTIME].Data);

	if(DialogItems[CFG_LONGOP].Selected)
		Opt.LongBeepTimeout = atoi(DialogItems[CFG_LONGOPTIME].Data);
	else
		Opt.LongBeepTimeout = 0;

	Opt.AskAbort           = DialogItems[CFG_ASKABORT].Selected;
	Opt.dDelimit           = DialogItems[CFG_DIGDEL].Selected;
	Opt.dDelimiter         = DialogItems[CFG_DIGCHAR].Data[0];
	Opt.ExtCmdView         = DialogItems[CFG_EXT].Selected;
	Opt.CmdLine            = Max(10,Min(FP_ConWidth()-9,atoi(DialogItems[CFG_EXT_W].Data)));
	Opt.CmdLength          = Max(5,Min(FP_ConHeight()-5,atoi(DialogItems[CFG_EXT_H].Data)));
	Opt.IOBuffSize         = Max((DWORD)FTR_MINBUFFSIZE,Str2Size(DialogItems[CFG_BUFFSIZE].Data));
	strcpy(Opt.DescriptionNames,DialogItems[CFG_DESC].Data);
	strcpy(Opt.DefaultPassword,DialogItems[CFG_PASS].Data);
	strcpy(Opt.Firewall,DialogItems[CFG_FIRE].Data);
	Opt.CmdLogLimit        = atoi(DialogItems[CFG_LOGLIMIT].Data);
	strcpy(Opt.CmdLogFile, DialogItems[CFG_LOGFILE].Data);
	Opt.LogOutput          = DialogItems[CFG_LOGDIR].Selected;
	Opt.PassiveMode        = DialogItems[CFG_PASV].Selected;
//Write to REG
	WriteCfg();

	if(FTPPanels[0]) FTPPanels[0]->Invalidate();

	if(FTPPanels[1]) FTPPanels[1]->Invalidate();

	return TRUE;
}