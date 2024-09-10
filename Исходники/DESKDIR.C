WORD
wrfile( char *fstr )
{
	REG int 	ret, retmsg;
	int 		inhand,outhand;
	int		time[2];
	DMABUFFER 	*mydta, *saved;
	char 		*buffer;
	long 		copysiz, bufsiz, wrsiz, tmpsiz; 
	int 		crted,sttime;
	char		buf[2];

	crted = 0;
	sttime = 1;
	retmsg = TRUE;
	rename = 0;
open:					/* open the source file	*/
	if ( ( inhand = (WORD)Fopen(fixsrc, 0) ) < 0 )		
	{				/* seek error or drive not ready */	
/*	  if ( (inhand == E_SEEK) || (inhand == EDRVNR) )
	    return( FALSE );
*/					/* skip	*/
	  if ( ( ret = fill_string( fixsrc, CNTOPEN ) ) == 1 )
	  {
	    updatnum(NUMFILE, --numfiles);
	    return SKIP;
	  }
	  else if (ret == 2)			/* retry */
		  goto open;
		else 				/* abort */
		  goto ww_3;
	}

	if ( !ch_undo() || f_cancel )		/* user want to stop */
	{
	  Fclose( inhand );
ww_3:	  f_abort = 1;
	  return( FALSE );
	}		  

	saved = (DMABUFFER *)Fgetdta();
	Fsetdta(mydta=(DMABUFFER *)malloc( (long)sizeof(DMABUFFER)));

	if ( Fsfirst( fixsrc, 0x37 ) )	
	{
	   retmsg = SKIP;
	   if ( do1_alert( RDERROR ) == 2 )	/* abort */
	   {
	     f_abort = 1;
	     retmsg = FALSE;
	   }
	   goto y2;
	}

	copysiz = mydta->d_fsize;
	buffer = (char *)malloc( copysiz );
	if ( buffer )
	{
	  bufsiz = copysiz;
	}
	else
	{
	  for (bufsiz = 128*1024L; bufsiz >= 1024L; bufsiz /= 2)
	  {
	    if ((buffer = (char *)malloc( bufsiz )) != 0)
	      break;
	  }
	  if (!buffer)
	    goto y2;
	}
  
	Fdatime( &time, inhand, 0 );	/* read the time and date */

rechkd:
	switch(chkdf(fstr, CPFILE))
	{
	    case CHECK:	
	      goto rechkd;

	    case SKIP:	
	      retmsg = SKIP;	
	      goto y1;

	    case QUIT:	
	      f_abort = 1;
	      retmsg = FALSE;
	      goto y1;

	    case FALSE:	
              retmsg = FALSE;
	      goto y1;
	}


	/* if it is move operation, then try rename first	*/

	if ( opcode == OP_MOVE )
	{			/* if same name and path, don't do it */
	  if ( strcmp( fixsrc, fixdst ) )
	    goto y22;
	
	  Fclose( inhand );

	  if ( Frename(0, fixsrc, fixdst) >= 0 )
   	  {	
	    inhand = (WORD)Fopen( fixdst, 0 );
	    if ( !p_timedate )		/* get the new time and date */
	    {
	      time[0] = Tgettime();
	      time[1] = Tgetdate();
	      Fdatime( &time, inhand, 1 ); 	
	    }
y22:	    
	    rename = 1;
	    goto y1;
	  }
	  else
	    inhand = (WORD)Fopen( fixsrc, 0 );		
	}


	while ( copysiz >= 0 ) 	/* let it passes through for zero file */
	{
	  tmpsiz = (copysiz > bufsiz) ? bufsiz : copysiz;
	  if (Fread(inhand, tmpsiz, buffer) < 0)	
	  {
	    retmsg = SKIP;
	    if ( crted )	
	      Fdelete( fixdst );

	    if (do1_alert( RDERROR ) == 2)	
	    {					/* abort */
	      f_abort = 1;
	      retmsg = FALSE;
	    }
	    goto y1;			/* skip */
	  }




create:
	  if ( sttime )
	  {
	    sttime = 0;

	    if ((outhand = (WORD)Fcreate(fixdst, mydta->d_fattr&7)) < 0)	
	    {
	      if ( ( ret = fill_string( fixdst, CNTCRTFL ) ) == 2 )
		goto create;

	      else if (ret == 3)				/* abort */
	      {
		 f_abort = 1;
		 retmsg = FALSE;
	      }
	      else	
		retmsg = SKIP;

	      goto y1;
	    }

	    crted = 1;
	  }

	  if ((wrsiz = Fwrite(outhand, tmpsiz, buffer)) < 0)	
	  {
	     retmsg = SKIP;
	     Fclose(outhand);
	     Fdelete(fixdst);

	    if (do1_alert( WRERROR ) == 2)	
	    {					/* abort */
	      f_abort = 1;
	      retmsg = FALSE;
	    }

	    goto y1;
	   }
				/* check if there are sufficent memory */
	   if (wrsiz != tmpsiz)		
	   { 			/* not sufficent memory ??*/
	      f_abort = 1;
	      retmsg = FALSE;
	      Fclose(outhand);	
	      Fdelete(fixdst);
	      buf[0] = *fixdst;
	      buf[1] = 0;
	      fill_string( buf, STDISKFU );
	      goto y1;
	   }

	   copysiz -= tmpsiz;
	   if ( !copysiz )
	     break;
	}

	if ( p_timedate )
	  Fdatime( &time, outhand, 1 );	

y0:
	Fclose(outhand);
y1:
	free(buffer);
y2:
	updatnum(NUMFILE, --numfiles);
	Fsetdta(saved);
y3:
	Fclose(inhand);
	free(mydta);

	if ( ( opcode == OP_MOVE ) && ( retmsg == TRUE ) )
	  upfdesk( fixsrc, fixdst );
	
	return(retmsg);
}