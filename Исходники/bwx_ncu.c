extern int
bwx_shell( struct bwb_line *l )
   {
   static char *s_buffer;
   static int init = FALSE;
   static int position;

   /* get memory for temporary buffer if necessary */

   if ( init == FALSE )
      {
      init = TRUE;

      /* Revised to CALLOC pass-thru call by JBV */
      if ( ( s_buffer = CALLOC( MAXSTRINGSIZE + 1, sizeof( char ),"bwx_shell" )) == NULL )
	 {
	 bwb_error( err_getmem );
	 return FALSE;
	 }
      }

   /* get the first element and check for a line number */

#if INTENSIVE_DEBUG
   sprintf( bwb_ebuf, "in bwx_shell(): line buffer is <%s>.", l->buffer );
   bwb_debug( bwb_ebuf );
#endif

   position = 0;
   adv_element( l->buffer, &position, s_buffer );
   if ( is_numconst( s_buffer ) != TRUE )                  /* not a line number */
      {

#if INTENSIVE_DEBUG
      sprintf( bwb_ebuf, "in bwx_shell(): no line number, command <%s>.",
	 l->buffer );
      bwb_debug( bwb_ebuf );
#endif
      nl();
      endwin(); /* Added by JBV 10/11/97 */
      if ( system( l->buffer ) == 0 )
	 {
         refresh(); /* Added by JBV 10/11/97 */
         nonl();
	 ncu_setpos();
	 return TRUE;
	 }
      else
	 {
         refresh(); /* Added by JBV 10/11/97 */
         nonl();
	 ncu_setpos();
	 return FALSE;
	 }
      }

   else                                         /* advance past line number */
      {
      adv_ws( l->buffer, &position );           /* advance past whitespace */

#if INTENSIVE_DEBUG
      sprintf( bwb_ebuf, "in bwx_shell(): line number, command <%s>.",
	 l->buffer );
      bwb_debug( bwb_ebuf );
#endif
      nl();
      endwin(); /* Added by JBV 10/11/97 */
      if ( system( &( l->buffer[ position ] ) ) == 0 )
	 {
         refresh(); /* Added by JBV 10/11/97 */
         nonl();
	 ncu_setpos();
	 return TRUE;
	 }
      else
	 {
         refresh(); /* Added by JBV 10/11/97 */
         nonl();
	 ncu_setpos();
	 return FALSE;
	 }
      }
   }