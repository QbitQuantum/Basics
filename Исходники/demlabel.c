USHORT demCreateLabel(BYTE Drive, LPSTR lpszName)
{
    CHAR szStr[32];
    CHAR szAnsi[32];
    CHAR szTmp[32];
    CHAR *p, *s;
    int  i = 0;


    sprintf(szStr, "%c:\\", Drive);

    s = lpszName;
    p = szTmp;

    while(s) {
	if(*s != '.')  {
	    *p = *s;
	    i++;
	    p++;
	}
	else {
	    while(i < 8) {
		*p++ = ' ';
		i++;
	    }
	}
	s++;

	if(i > 11)
	    break;
    }

    szTmp[i] = '\0';

    OemToAnsi(szTmp, szAnsi);

    if(!SetVolumeLabelA(szStr, szAnsi))
	return(1);

    else
	return(0);


}