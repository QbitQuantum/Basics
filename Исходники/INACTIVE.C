/* HandleAvailable()
 * ===================================================================
 */
int
HandleAvailable( int button, WORD *msg )
{
   int     quit;
   int     dclick;
   FON_PTR curptr;

   
   dclick = FALSE;  
   quit   = FALSE;
      
   /* Handle Double-clicking of the objects */   
   if( ( button != -1 ) && ( button & 0x8000 ) )
   {
      button &= 0x7FFF;
      dclick = TRUE;
   }   
   
   switch( button )
   {
     case IEXIT:    Deselect( IEXIT );

		    ClearFnodes( installed_list );
		    ClearFnodes( available_list );

		    Reset_Tree( ad_front );     

		    CheckInstallAll( FALSE );
		    		    
                    mover_setup( installed_list, installed_count,
		                 FBASE, FSLIDER, FUP, FDOWN,
		  		 LINE0, LINE13, LINEBASE, 0, FRONT_HEIGHT );
		    HideObj( LINEBASE );	  		 
		    Objc_draw( tree, ROOT, MAX_DEPTH, NULL ); 
		    ShowObj( LINEBASE );
		    RedrawBase( tree, LINEBASE );
     		    break;

     case ILINE0:
     case ILINE1:
     case ILINE2:
     case ILINE3:
     case ILINE4:
     case ILINE5:
     case ILINE6:
     case ILINE7:
     case ILINE8:
     case ILINE9:
     case ILINE10:
     case ILINE11:
     case ILINE12:
     case ILINE13:  if( dclick )
     		    {
	              curptr = Active_Slit[ button - First_Obj ];
	              if( !curptr )
	      	          return( quit );	      
		      DoPoints( tree, button );
     		    }
     		    else
     		      mover_button( button, dclick );
     		    break;


     case IUP:
     case IDOWN:
     case IBASE:
     case ISLIDER:  mover_button( button, dclick );
		    break;


     case IINSTALL: if( IsChanged( available_list ) )
     		    {  
 		       /* ASK if we want it install these fonts first.*/
		       if( form_alert( 1, alert58 ) == 2 )
		       {
		           XDeselect( tree, IINSTALL );
		           return( quit );
		       }       
		       MoveToInstalled( FALSE );
     		    }   
    		    XDeselect( tree, IINSTALL );
     		    break;

     case ICONFIG:  Deselect( ICONFIG );
		    if( DoPoints( ad_inactive, 0 ))
		       XDeselect( tree, ICONFIG );
		    break;

     case ISELECT:  DoSelectAll();
		    XDeselect( tree, ISELECT );
     		    break;
     		    
     default:	 if( button == -1 )
     		 {
     		   switch( msg[0] )
     		   {
     		     case WM_REDRAW: 
     		     		     break;
     			     		     
     		     case AC_CLOSE:  quit = TRUE;
     		     		     break;
     				     		     
     		     case WM_CLOSED: quit = TRUE;
     		     		     CloseWindow();
				     break;

		     case CT_KEY:    if( msg[3] == UNDO )
				        Undo_Fnodes( available_list, ( FON_PTR )NULL );
		     		     break;
     		     default:
     		     		break;
     		   }
     		 }
     		 else
	           Undo_Fnodes( available_list, ( FON_PTR )NULL );
     		 break;
   }
   return( quit );

}