void fputtr_internal(FILE *fp, segy *tp, cwp_Bool fixed_length)
{
	/* search linked list for possible alternative */
	if(fp != lastfp)  searchlist(fp);

	if (infoptr == ((struct outsegyinfo *) NULL)) {
		/* initialize new segy output stream */

		/* allocate new segy output information table */
		*oldinfoptr = (struct outsegyinfo *)
			malloc(sizeof(struct outsegyinfo));
		infoptr = *oldinfoptr;
		infoptr->nextinfo = (struct outsegyinfo *) NULL;
		/* save FILE * ptr */
		infoptr->outfp = fp;
		infoptr->itr = 0;

		switch (infoptr->ftype = filestat(fileno(fp))) {
		case DIRECTORY:
			err("%s: segy output can't be a directory", __FILE__);
		case TTY:
			err("%s: segy output can't be tty", __FILE__);
		default:
			/* the rest are ok */
		break;
		}

		/* Sanity check the segy header */
		infoptr->nsfirst = tp->ns;
		if (infoptr->nsfirst > SU_NFLTS)
			err("%s: unable to handle %d > %d samples per trace",
			    __FILE__, infoptr->nsfirst, SU_NFLTS);
		switch(tp->trid) {
		case CHARPACK:
			infoptr->bytesper = sizeof(char); break;
		case SHORTPACK:
			infoptr->bytesper = 2*sizeof(char); break;
		default:
			infoptr->bytesper = sizeof(float); break;
		}

/*--------------------------------------------------------------------*\
   Write out a line header if it has been set as the default or has 
   requested on the caommandline.  Commandline takes precedence over
   the default in all cases.

   Reginald H. Beardsley			    [email protected]
\*--------------------------------------------------------------------*/
	      
		if (!getparint( "lheader" ,&out_line_hdr )) out_line_hdr=0;

		if( out_line_hdr ){

		   if( in_line_hdr ){
		     (void) efwrite(&(su_text_hdr[0]), 1 ,3200 
				    ,infoptr->outfp);

		   }else{
		     memset( su_text_hdr ,0 ,sizeof(su_text_hdr) );
		     sprintf( hdr_str ,"%-80s" 
			    ,"C 1 CLIENT CWP/SU default text header " );
		     strncat( su_text_hdr ,hdr_str ,80 );
		     for( i=1; i<40; i++ ){
			sprintf( hdr_str ,"%-80s" ,"C" );
			strncat( su_text_hdr ,hdr_str ,80 );
		     }
		     (void) efwrite(&(su_text_hdr[0]), 1 ,3200 
				    ,infoptr->outfp);


		   }

		   memset( &su_binary_hdr ,0 ,sizeof(su_binary_hdr) );
		   su_binary_hdr.format = 5;
		   su_binary_hdr.hns = tp->ns;
		   su_binary_hdr.hdt = tp->dt;
 
 
		  (void) efwrite(&su_binary_hdr,1,
			sizeof(su_binary_hdr), infoptr->outfp);
		}
		
	}

	if (tp->ns != infoptr->nsfirst && fixed_length)
		err("%s: on trace #%ld, number of samples in header (%d) "
		    "differs from number for first trace (%d)", 
		    __FILE__, (infoptr->itr)+1, tp->ns, infoptr->nsfirst);
	

	(void) efwrite(tp, 1,HDRBYTES, infoptr->outfp);
	datawrite(tp, infoptr, fixed_length);
	
	++infoptr->itr;
	lastfp = infoptr->outfp;
}