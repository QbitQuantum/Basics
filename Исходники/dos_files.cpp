Bit8u FCB_Parsename(Bit16u seg,Bit16u offset,Bit8u parser ,char *string, Bit8u *change) {
	char * string_begin=string;
	Bit8u ret=0;
	if (!(parser & PARSE_DFLT_DRIVE)) {
		// default drive forced, this intentionally invalidates an extended FCB
		mem_writeb(PhysMake(seg,offset),0);
	}
	DOS_FCB fcb(seg,offset,false);	// always a non-extended FCB
	bool hasdrive,hasname,hasext,finished;
	hasdrive=hasname=hasext=finished=false;
	Bitu index=0;
	Bit8u fill=' ';
/* First get the old data from the fcb */
#ifdef _MSC_VER
#pragma pack (1)
#endif
	union {
		struct {
			char drive[2];
			char name[9];
			char ext[4];
		} GCC_ATTRIBUTE (packed) part;
		char full[DOS_FCBNAME];
	} fcb_name;
#ifdef _MSC_VER
#pragma pack()
#endif
	/* Get the old information from the previous fcb */
	fcb.GetName(fcb_name.full);
	fcb_name.part.drive[0]-='A'-1;fcb_name.part.drive[1]=0;
	fcb_name.part.name[8]=0;fcb_name.part.ext[3]=0;
	/* Strip of the leading sepetaror */
	if((parser & PARSE_SEP_STOP) && *string)  {       //ignore leading seperator
		char sep[] = FCB_SEP;char a[2];
		a[0]= *string;a[1]='\0';
		if (strcspn(a,sep)==0) string++;
	} 
	/* strip leading spaces */
	while((*string==' ')||(*string=='\t')) string++;
	/* Check for a drive */
	if (string[1]==':') {
		fcb_name.part.drive[0]=0;
		hasdrive=true;
		if (isalpha(string[0]) && Drives[toupper(string[0])-'A']) {
			fcb_name.part.drive[0]=(char)(toupper(string[0])-'A'+1);
		} else ret=0xff;
		string+=2;
	}
	/* Special checks for . and .. */
	if (string[0]=='.') {
		string++;
		if (!string[0])	{
			hasname=true;
			ret=PARSE_RET_NOWILD;
			strcpy(fcb_name.part.name,".       ");
			goto savefcb;
		}
		if (string[1]=='.' && !string[1])	{
			string++;
			hasname=true;
			ret=PARSE_RET_NOWILD;
			strcpy(fcb_name.part.name,"..      ");
			goto savefcb;
		}
		goto checkext;
	}
	/* Copy the name */	
	hasname=true;finished=false;fill=' ';index=0;
	while (index<8) {
		if (!finished) {
			if (string[0]=='*') {fill='?';fcb_name.part.name[index]='?';if (!ret) ret=1;finished=true;}
			else if (string[0]=='?') {fcb_name.part.name[index]='?';if (!ret) ret=1;}
			else if (isvalid(string[0])) {fcb_name.part.name[index]=(char)(toupper(string[0]));}
			else { finished=true;continue; }
			string++;
		} else {
			fcb_name.part.name[index]=fill;
		}
		index++;
	}
	if (!(string[0]=='.')) goto savefcb;
	string++;
checkext:
	/* Copy the extension */
	hasext=true;finished=false;fill=' ';index=0;
	while (index<3) {
		if (!finished) {
			if (string[0]=='*') {fill='?';fcb_name.part.ext[index]='?';finished=true;}
			else if (string[0]=='?') {fcb_name.part.ext[index]='?';if (!ret) ret=1;}
			else if (isvalid(string[0])) {fcb_name.part.ext[index]=(char)(toupper(string[0]));}
			else { finished=true;continue; }
			string++;
		} else {
			fcb_name.part.ext[index]=fill;
		}
		index++;
	}
savefcb:
	if (!hasdrive & !(parser & PARSE_DFLT_DRIVE)) fcb_name.part.drive[0] = 0;
	if (!hasname & !(parser & PARSE_BLNK_FNAME)) strcpy(fcb_name.part.name,"        ");
	if (!hasext & !(parser & PARSE_BLNK_FEXT)) strcpy(fcb_name.part.ext,"   ");
	fcb.SetName(fcb_name.part.drive[0],fcb_name.part.name,fcb_name.part.ext);
	*change=(Bit8u)(string-string_begin);
	return ret;
}