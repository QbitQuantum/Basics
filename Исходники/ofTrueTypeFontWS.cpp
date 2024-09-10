//=====================================================================
void ofTrueTypeFontWS::drawStringAsShapes(wstring c, float x, float y) {
  
  if (!bLoadedOk){
    ofLog(OF_LOG_ERROR,"Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    return;
  };
  
	//----------------------- error checking
	if (!bMakeContours){
		ofLog(OF_LOG_ERROR,"Error : contours not created for this font - call loadFont with makeContours set to true");
		return;
	}
  
  int len = (int)c.length();
  // if (less_func(NUM_MAX_CHARACTERS, len + getLoadedCharsNum())) {
  //   ofLog(OF_LOG_ERROR,"Error : too many typefaces already loaded");
  //   return;
  // }
  
	GLint		index	= 0;
	GLfloat		X		= 0;
	GLfloat		Y		= 0;
  
	glPushMatrix();
	glTranslatef(x, y, 0);
  
	while(index < len){
		int cy = getCharID(c[index]);
    if (cps[cy].value == TYPEFACE_UNLOADED){
      loadEachChar(cy);
    }
		if (cy < nCharacters){ 			// full char set or not?
		  if (c[index] == L'\n') {
        
				Y = lineHeight;
				X = 0 ; //reset X Pos back to zero
        
		  }else if (c[index] == L' ') {
        cy = getCharID(L'p');
        X += cps[cy].width;
        //glTranslated(cps[cy].width, 0, 0);
		  } else {
				drawCharAsShape(cy, X, Y);
				X += cps[cy].setWidth;
				//glTranslated(cps[cy].setWidth, 0, 0);
		  }
		}
		index++;
	}
  
	glPopMatrix();
  
}