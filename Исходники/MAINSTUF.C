/* initialize()
 * ====================================================================
 */
int
initialize( void )
{
      int berror;
      int flag;
      
      flag = TRUE;
            
      /* Get the Boot Drive and Muck the paths */
      Drive = GetBaseDrive();
      OnPath[0] = OffPath[0] = Drive;
      NPOnPath[0] = NPOffPath[0] = Drive;
          

      olddma = Fgetdta();	
      Fsetdta( &newdma );		/* Point to OUR buffer */

     berror = Fsfirst( OnPath, 0 );
     if( berror == E_OK )		/* Found it! */
     {
	/* MINT IS ON! with Memory Protection */
	Select( SETON );
	Deselect( SETOFF );
	Select( NPON );
	Deselect( NPOFF );
	bstate = TRUE;
	cstate = TRUE;
     }
     else
     {
        /* Check for No Memory Protection */
        berror = Fsfirst( NPOnPath, 0 );
        if( berror == E_OK )
        {
           /* Found it! It is ON with No Memory Protection */
	   Select( NPOFF );
	   Deselect( NPON );
	   Select( SETON );
	   Deselect( SETOFF );
	   bstate = TRUE;
           cstate = FALSE;
        }
        else
        {
     	   /* Check for Off items */
     
           /* Mint is OFF, with memory protection */
           berror = Fsfirst( OffPath, 0 );
           if( berror == E_OK )		/* Found it! */
           {
             /* MInT.PRX is found! */
             Select( SETOFF );
             Deselect( SETON );
             Select( NPON );
             Deselect( NPOFF );
             bstate = FALSE;
             cstate = TRUE;
           }
           else
           {
              /* Mint is off with no memory protection */
              berror = Fsfirst( NPOffPath, 0 );
              if( berror == E_OK )
              {
                /* MintNP.prx is found */
                Select( SETOFF );
                Deselect( SETON );
                Select( NPOFF );
                Deselect( NPON );
                bstate = FALSE;
                cstate = FALSE;
              }
              else
              {
       	        /* Mint is not on the hard disk...*/
	        form_alert( 1, nomint );
	        flag = FALSE;
	      }  
           }
       }   
     }
     Fsetdta( olddma );		/* Point to OLD buffer */
     return( flag );
}