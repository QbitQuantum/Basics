void EyeDx(char *up_filename,	/* filename of up-image to process; may be empty */
		   char *side_filename,	/* filename of side-image to process; may be empty */
		   int SideOrientation,	/* 0 means left, otherwise right */
		   int FULL_FLAG)		/* flag on outputing full-size annotated images */

{
char	text[250],text1[250],text2[250],savepath[150];
char	BrowserCommand[MAX_FILENAME_CHARS],BrowserPath[MAX_FILENAME_CHARS];
int		up_report,side_report,i;
double	up_lefteye_circles[4],up_righteye_circles[4];
double	side_lefteye_circles[4],side_righteye_circles[4];
int		up_strabismus,side_strabismus;
int		up_red_reflex_lumin,side_red_reflex_lumin;
int		up_left_arr_class,up_right_arr_class;
int		side_left_arr_class,side_right_arr_class;
int		up_left_arr_row,up_left_arr_col;
int		up_right_arr_row,up_right_arr_col;
int		side_left_arr_row,side_left_arr_col;
int		side_right_arr_row,side_right_arr_col,Referral;
FILE	*fpt;
struct tm *newtime;
time_t	aclock;
HANDLE	hFind;
WIN32_FIND_DATA	fd;
HKEY	hKeyHTML,hKeyCommand;
DWORD	Type,Bytes;
char	strab_names[6][20]={"N.A.","NONE","EXOTROPIA","ESOTROPIA",\
					"HYPERTROPIA","NOT LOOKING?"};
char	lumin_names[4][20]={"N.A.","NORMAL","NOT_DETECTED","UNEQUAL"};
char	arr_names[4][20]={"N.A.","NONE","CRESCENT","OTHER"};


		/*********************************************************
		** Process given images.  Result for each image is an eye
		** model (two concentric circles), a strabismus value (0-5),
		** a red reflex luminensce value (0-3), and left & right
		** abnormal red reflex values (0-3).
		*********************************************************/

if (strcmp(up_filename,"") != 0)
  up_report=ProcessImage(up_filename,0,up_lefteye_circles,
	up_righteye_circles,&up_strabismus,&up_red_reflex_lumin,
	&up_left_arr_class,&up_right_arr_class,&up_left_arr_col,
	&up_left_arr_row,&up_right_arr_col,&up_right_arr_row,
	FULL_FLAG,1);
else
  up_report=-1;
if (strcmp(side_filename,"") != 0  &&  SideOrientation == 0)
  side_report=ProcessImage(side_filename,1,side_lefteye_circles,
	side_righteye_circles,&side_strabismus,&side_red_reflex_lumin,
	&side_left_arr_class,&side_right_arr_class,&side_left_arr_col,
	&side_left_arr_row,&side_right_arr_col,&side_right_arr_row,
	FULL_FLAG,1);
else if (strcmp(side_filename,"") != 0  &&  SideOrientation != 0)
  side_report=ProcessImage(side_filename,2,side_lefteye_circles,
	side_righteye_circles,&side_strabismus,&side_red_reflex_lumin,
	&side_left_arr_class,&side_right_arr_class,&side_left_arr_col,
	&side_left_arr_row,&side_right_arr_col,&side_right_arr_row,
	FULL_FLAG,1);
else
  side_report=-1;

		/*********************************************************
		** Make referral decision based on reports
		*********************************************************/

Referral=0;	/* don't refer */
if (up_report >= 0  &&  side_report >= 0)
  {
  if (up_strabismus == 5  ||  side_strabismus == 5  ||
		(up_strabismus == 0  &&  side_strabismus == 0))
    Referral=2;	/* retry */
  if (Referral == 0  &&  (up_strabismus > 1  ||  side_strabismus > 1  ||
		up_red_reflex_lumin == 2  ||  side_red_reflex_lumin == 2  ||
		up_right_arr_class > 1  ||  up_left_arr_class > 1  ||
		side_right_arr_class > 1  ||  side_left_arr_class > 1))
	Referral=1;	/* refer */
  if (Referral == 1  &&  up_strabismus == 1  &&  side_strabismus == 1  &&
	    up_red_reflex_lumin == 1  &&  side_red_reflex_lumin == 1  &&
		up_right_arr_class >= 1  &&  up_right_arr_class <= 2  &&
		up_left_arr_class >= 1  &&  up_left_arr_class <= 2  &&
		side_right_arr_class >= 1  &&  side_right_arr_class <= 2  &&
		side_left_arr_class >= 1  &&  side_left_arr_class <= 2)
	if (DialogBox(hInst,"ID_ONE_YEAR_DIALOG",MainWnd,(DLGPROC)YesNoDlgProc) == IDYES)
	  Referral=0;	/* crescent only, less than one year old = don't refer */
/*
    fprintf(fpt,"Strabismus: <B> %s, %s </B><P>\n",strab_names[up_strabismus],
		strab_names[side_strabismus]);
    fprintf(fpt,"Red Reflex: <B> %s, %s </B><P>\n",
		lumin_names[up_red_reflex_lumin],
		lumin_names[side_red_reflex_lumin]);
    fprintf(fpt,"Abnormal Pupil Area: <B> %s, %s ; %s , %s </B><P>\n",
		arr_names[up_right_arr_class],arr_names[up_left_arr_class],
		arr_names[side_right_arr_class],arr_names[side_left_arr_class]);
*/
  }
else if (up_report >= 0)
  {
  if (up_strabismus == 5  ||  up_strabismus == 0)
    Referral=2;	/* retry */
  if (Referral == 0  &&  (up_strabismus > 1  ||  up_red_reflex_lumin == 2  ||
		up_right_arr_class > 1  ||  up_left_arr_class > 1))
    Referral=1;	/* refer */
  if (Referral == 1  &&  side_strabismus == 1  &&
	    side_red_reflex_lumin == 1  &&
		side_right_arr_class >= 1  &&  side_right_arr_class <= 2  &&
		side_left_arr_class >= 1  &&  side_left_arr_class <= 2)
	if (DialogBox(hInst,"ID_ONE_YEAR_DIALOG",MainWnd,(DLGPROC)YesNoDlgProc) == IDYES)
	  Referral=0;	/* crescent only, less than one year old = don't refer */
/*
    fprintf(fpt,"Strabismus: <B> %s </B><P>\n",strab_names[up_strabismus]);
    fprintf(fpt,"Red Reflex: <B> %s </B><P>\n",lumin_names[up_red_reflex_lumin]);
    fprintf(fpt,"Abnormal Pupil Area: <B> %s, %s </B><P>\n",
		arr_names[up_right_arr_class],arr_names[up_left_arr_class]);
*/
  }
else if (side_report >= 0)
  {
  if (side_strabismus == 5  ||  side_strabismus == 0)
    Referral=2;	/* retry */
  if (Referral == 0  &&  (side_strabismus > 1  ||  side_red_reflex_lumin == 2  ||
		side_right_arr_class > 1  ||  side_left_arr_class > 1))
    Referral=1;	/* refer */
  if (Referral == 1  &&  up_strabismus == 1  &&
	    up_red_reflex_lumin == 1  &&
		up_right_arr_class >= 1  &&  up_right_arr_class <= 2  &&
		up_left_arr_class >= 1  &&  up_left_arr_class <= 2)
	if (DialogBox(hInst,"ID_ONE_YEAR_DIALOG",MainWnd,(DLGPROC)YesNoDlgProc) == IDYES)
	  Referral=0;	/* crescent only, less than one year old = don't refer */
/*
    fprintf(fpt,"Strabismus: <B>%s</B><P>\n",strab_names[side_strabismus]);
    fprintf(fpt,"Red Reflex: <B>%s</B><P>\n",lumin_names[side_red_reflex_lumin]);
    fprintf(fpt,"Abnormal Pupil Area: <B> %s, %s </B><P>\n",
		arr_names[side_right_arr_class],arr_names[side_left_arr_class]);
*/
  }

		/*********************************************************
		** Write graphic and/or letter report
		*********************************************************/

time( &aclock );                 /* Get time in seconds */
newtime = localtime( &aclock );  /* Convert time to struct tm form */
if (/* DisplayGraphics == */1)
  {
  strcpy(savepath,DataPath);
  if (savepath[strlen(savepath)-1] != '\\')
	strcat(savepath,"\\");
  strcat(savepath,"reports");
  if ((hFind=FindFirstFile(savepath,&fd)) == INVALID_HANDLE_VALUE)
    {
    if (!CreateDirectory(savepath,NULL))
	  {
	  MessageBox(NULL,"Saving report","Unable to create reports folder; saving in runtime folder",
		  MB_APPLMODAL | MB_OK);
	  strcpy(savepath,".");
	  }
    }

  FindClose(hFind);

  if (up_report >= 0)
    StripFilename(up_filename,text1);
  if (side_report >= 0)
    StripFilename(side_filename,text2);
  /*
  if (up_report >= 0  &&  side_report >= 0)
    sprintf(text,"%s\\%s-%s.htm",savepath,text1,text2);
  else if (up_report >= 0)
    sprintf(text,"%s\\%s.htm",savepath,text1);
  else
    sprintf(text,"%s\\%s.htm",savepath,text2);
  */
  sprintf(text,"%s\\%s.htm",savepath,report_filename);
  if ((fpt=fopen(text,"w")) == NULL)
    {
    MessageBox(MainWnd,text,"Unable to open report for writing:",MB_APPLMODAL | MB_OK);
    exit(0);
    }
  fprintf(fpt,"<TITLE>EyeDx Photoscreening Results</TITLE>\n");
  fprintf(fpt,"<CENTER><H3>EyeDx Photoscreening Results:  %s</H3><P>\n",report_filename);
  fprintf(fpt,"<H3>Referral recommended: ");
  if (Referral == 1)
	fprintf(fpt,"Yes");
  else if (Referral == 0)
	fprintf(fpt,"No");
  else
	fprintf(fpt,"Image(s) unclear.  Please repeat.");
  fprintf(fpt,"</H3><P>\n<CENTER>\n\n");
  fprintf(fpt,"<TABLE BORDER=3 CELLSPACING=2 CELLPADDING=2>\n");
  fprintf(fpt,"<TR ALIGN=CENTER> ");
  if (up_report >= 0)
    fprintf(fpt,"<TD> Photo ID:  %s (up) ",text1);
  if (side_report >= 0)
    fprintf(fpt,"<TD> Photo ID:  %s (%s) ",text2,
		(SideOrientation == 0 ? "left" : "right"));
  fprintf(fpt,"\n");
    fprintf(fpt,"<TR> ");
  if (up_report >= 0)
    fprintf(fpt,"<TD> <IMG HEIGHT=240 WIDTH=320 SRC=\"..\\Simages\\S%s\">\n",&(up_filename[1]));
  if (side_report >= 0)
    fprintf(fpt,"<TD> <IMG HEIGHT=240 WIDTH=320 SRC=\"..\\Simages\\S%s\">\n",&(side_filename[1]));
  fprintf(fpt,"\n");

  fprintf(fpt,"<TR ALIGN=CENTER> ");
  if (up_report >= 0)
    {
    fprintf(fpt,"<TD> <TABLE BORDER=1 CELLSPACING=2 CELLPADDING=2>\n");
    fprintf(fpt,"  <TR ALIGN=CENTER> <TD> ");
    if (up_report == 0)
      fprintf(fpt,"Please try another photograph.\n");
    else
      {
      fprintf(fpt,"<IMG HEIGHT=150 WIDTH=150 SRC=\"..\\eyes\\%s.right_raw.jpg\">\n",text1);
      fprintf(fpt,"  <TD> <IMG HEIGHT=150 WIDTH=150 SRC=\"..\\eyes\\%s.left_raw.jpg\">\n",text1);
      }
    fprintf(fpt,"  </TABLE><P>\n");
    }
  if (side_report >= 0)
    {
    fprintf(fpt,"<TD> <TABLE BORDER=1 CELLSPACING=2 CELLPADDING=2>\n");
    fprintf(fpt,"  <TR ALIGN=CENTER> <TD> ");
    if (side_report == 0)
      fprintf(fpt,"Please try another photograph.\n");
    else
      {
      fprintf(fpt,"<IMG HEIGHT=150 WIDTH=150 SRC=\"..\\eyes\\%s.right_raw.jpg\">\n",text2);
      fprintf(fpt,"  <TD> <IMG HEIGHT=150 WIDTH=150 SRC=\"..\\eyes\\%s.left_raw.jpg\">\n",text2);
      }
    fprintf(fpt,"  </TABLE><P>\n");
    }
  if (1 /* DisplayGraphics == 1 */)
    {
    fprintf(fpt,"<TR ALIGN=CENTER> ");
    if (up_report >= 0)
      {
      fprintf(fpt,"<TD> <TABLE BORDER=1 CELLSPACING=2 CELLPADDING=2>\n");
      fprintf(fpt,"  <TR ALIGN=CENTER> <TD> ");
      if (up_report == 0)
        fprintf(fpt,"Photo inconclusive.\n");
      else
        {
        fprintf(fpt,"<IMG HEIGHT=150 WIDTH=150 SRC=\"..\\eyes\\%s.right_eye.jpg\">\n",text1);
        fprintf(fpt,"  <TD> <IMG HEIGHT=150 WIDTH=150 SRC=\"..\\eyes\\%s.left_eye.jpg\">\n",text1);
        }
      fprintf(fpt,"  </TABLE><P>\n");
      }
    if (side_report >= 0)
      {
      fprintf(fpt,"<TD> <TABLE BORDER=1 CELLSPACING=2 CELLPADDING=2>\n");
      fprintf(fpt,"  <TR ALIGN=CENTER> <TD> ");
      if (side_report == 0)
        fprintf(fpt,"Photo inconclusive.\n");
      else
        {
        fprintf(fpt,"<IMG HEIGHT=150 WIDTH=150 SRC=\"..\\eyes\\%s.right_eye.jpg\">\n",text2);
        fprintf(fpt,"  <TD> <IMG HEIGHT=150 WIDTH=150 SRC=\"..\\eyes\\%s.left_eye.jpg\">\n",text2);
       }
      fprintf(fpt,"  </TABLE><P>\n");
      }
	}
  fprintf(fpt,"</TABLE><P>\n");
  fprintf(fpt,"</CENTER>\n\n");
  fprintf(fpt,"EyeDx screening estimates refractive errors, strabismus and pupil opacities.\n");
  fprintf(fpt,"Please be aware of the tolerances of the system noted in your manual.\n");
  fprintf(fpt,"Display of annotated eyes is for viewing purposes only and is not required\n");
  fprintf(fpt,"by the EyeDx software to provide the referral recommendation.\n");
  fprintf(fpt,"Patent pending.\n");

  fprintf(fpt,"\n<HR>\n\n");
  fprintf(fpt,"<ADDRESS> [email protected] / %s / %s </A></ADDRESS>\n",Version,asctime(newtime));
  fclose(fpt);
  }
if (1 /* AutoReport == 1 */)
  {		/* look in Windows registry for default command to open html file */
  if (RegOpenKeyEx(HKEY_CLASSES_ROOT,".htm",0,KEY_ALL_ACCESS,&hKeyHTML) == ERROR_SUCCESS)
    {
	Bytes=250;
	RegQueryValueEx(hKeyHTML,"",0,&Type,text1,&Bytes);
	strcat(text1,"\\shell\\open\\command");
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT,text1,0,KEY_ALL_ACCESS,&hKeyCommand) == ERROR_SUCCESS)
	  {
	  Bytes=MAX_FILENAME_CHARS;
	  RegQueryValueEx(hKeyCommand,"",0,&Type,BrowserCommand,&Bytes);
	  i=1;
	  while (BrowserCommand[i] != ':'  ||  BrowserCommand[i+1] != '\\')
		i++;
	  strcpy(BrowserPath,&(BrowserCommand[i-1]));
	  i=0;
	  while (i < (int)strlen(BrowserPath)  &&  BrowserPath[i] != ' ')
		i++;
	  while (i > 0  &&  !(BrowserPath[i] == 'e'  ||  BrowserPath[i] == 'E'))
		i--;
	  BrowserPath[i+1]='\0';
	  RegCloseKey(hKeyCommand);
	  i=strlen(BrowserPath)-1;
	  while (BrowserPath[i] != '\\')
		i--;
	  strcpy(BrowserCommand,&(BrowserPath[i+1]));
	  }
	else
	  {
	  strcpy(BrowserPath,"NotGoingToWork");
	  strcpy(BrowserCommand,"CouldNotFindIt");
	  }
	RegCloseKey(hKeyHTML);
    if (_spawnlp(_P_NOWAIT,BrowserPath,BrowserCommand,text,NULL) == -1)
      MessageBox(NULL,"Unable to start web browser.\nPlease display report manually.",
				"Report finished",MB_OK | MB_APPLMODAL);
	}
  else	/* try some default locations... */
	{
    if (_spawnlp(_P_NOWAIT,"C:\\Program Files\\Netscape\\Navigator\\Program\\netscape","netscape",text,NULL) == -1)
      if (_spawnlp(_P_NOWAIT,"C:\\Program Files\\Netscape\\Communicator\\Program\\netscape","netscape",text,NULL) == -1)
        MessageBox(NULL,"Unable to start web browser.\nPlease display report manually.",
				"Report finished",MB_OK | MB_APPLMODAL);
	}
  }
}