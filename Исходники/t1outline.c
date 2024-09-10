/* T1_SetChar(...): Generate the bitmap for a character */
T1_OUTLINE *T1_GetCharOutline( int FontID, char charcode, float size,
			       T1_TMATRIX *transform)
{
  int i;
  int mode;
  T1_PATHSEGMENT *charpath;
  struct XYspace *Current_S;
  unsigned char ucharcode;
  
  
  FONTSIZEDEPS *font_ptr;
  FONTPRIVATE  *fontarrayP;
  
  /* We don't implement underlining for characters, but the rasterer
     implements it. Thus, we use a modflag of constant 0 */
  int modflag=0;

  
  /* We return to this if something goes wrong deep in the rasterizer */
  if ((i=setjmp( stck_state))!=0) {
    T1_errno=T1ERR_TYPE1_ABORT;
    sprintf( err_warn_msg_buf, "t1_abort: Reason: %s",
	     t1_get_abort_message( i));
    T1_PrintLog( "T1_GetCharOutline()", err_warn_msg_buf,
	       T1LOG_ERROR);
    return( NULL);
  }

  ucharcode=(unsigned char)charcode;

  
  /* First, check for a correct ID */
  i=CheckForFontID(FontID);
  if (i==-1){
    T1_errno=T1ERR_INVALID_FONTID;
    return(NULL);
  }
  /* if necessary load font into memory */
  if (i==0)
    if (T1_LoadFont(FontID))
      return(NULL);

  /* Check for valid size */
  if (size<=0.0){
    T1_errno=T1ERR_INVALID_PARAMETER;
    return(NULL);
  }

  fontarrayP=&(pFontBase->pFontArray[FontID]);
  
  /* font is now loaded into memory =>
     Check for size: */
  if ((font_ptr=QueryFontSize( FontID, size, NO_ANTIALIAS))==NULL){
    font_ptr=CreateNewFontSize( FontID, size, NO_ANTIALIAS);
    if (font_ptr==NULL){
      T1_errno=T1ERR_ALLOC_MEM;
      return(NULL);
    }
  }
  
  /* Setup an appropriate charspace matrix. Note that the rasterizer
     assumes vertical values with inverted sign! Transformation should
     create a copy of the local charspace matrix which then still has
     to be made permanent. */
  if (transform!=NULL) {
    Current_S=(struct XYspace *) 
      Permanent(Scale(Transform (font_ptr->pCharSpaceLocal,
				 transform->cxx, - transform->cxy,
				 transform->cyx, - transform->cyy),
		      DeviceSpecifics.scale_x, DeviceSpecifics.scale_y));
  }
  else{
    Current_S=(struct XYspace *)
      Permanent(Scale(Transform(font_ptr->pCharSpaceLocal,
				1.0, 0.0, 0.0, -1.0),
		      DeviceSpecifics.scale_x, DeviceSpecifics.scale_y));
  }

  
  /* fnt_ptr now points to the correct FontSizeDeps-struct =>
     lets now raster the character */
  mode=0;
  charpath=(T1_PATHSEGMENT *)fontfcnB( FontID, modflag, Current_S,
				       fontarrayP->pFontEnc,
				       ucharcode, &mode,
				       fontarrayP->pType1Data,
				       DO_NOT_RASTER);
  KillSpace (Current_S);

  return((T1_OUTLINE *)charpath);
}