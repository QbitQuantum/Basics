int 
GvMField::ioValue(AStream &a)
{
    char c;
    int	curIndex = 0;

	if (a.IsInput()) {
    	c = a.Skip();
    	if (c == OPEN_BRACE_CHAR) {
			  c = a.getc();
			  c = a.Skip();

			  if (CLOSE_BRACE_CHAR) {
			  	 c = a.getc();
	    	   }						
			   else {

	    		while (TRUE) {

				if (curIndex >= num)
		    		makeRoom(curIndex + 1);

				if (!io1Value(a, curIndex++) ) {
		    		a.Error( "Couldn't read value %d of field",  curIndex);
		    	    return FALSE;
				}
				c = a.Skip();

				if (c == VALUE_SEPARATOR_CHAR) {
 				    c = a.getc();
		    		c = a.Skip();
					if (c == CLOSE_BRACE_CHAR) {
 				       c = a.getc();
			    	   break;
					}
				}

				else if (c == CLOSE_BRACE_CHAR) {
 				    c = a.getc();
		    		break;
				}
				else {
		    		a.Error("Expected '%c' or '%c' but got "
				      "'%c' while reading value %d",
				      VALUE_SEPARATOR_CHAR,
				      CLOSE_BRACE_CHAR, c,
				      curIndex);
		    		return FALSE;
				}
	    		} // While 
			}

	if (curIndex < num)
	    makeRoom(curIndex);
    
    }  // no open brace
    else {
		makeRoom(1);
		if (! io1Value(a, 0))
	    return FALSE;
    }
	}	// input 
	else { // output 

		if (Length() == 0 ) {
		  a.Sep(OPEN_BRACE_CHAR);
		  a.Sep(CLOSE_BRACE_CHAR);

		} else 
		if (Length() == 1 ) {
		   io1Value(a,0);
		} else {
		a.Sep(OPEN_BRACE_CHAR); a.TabIn();
		while (curIndex < Length()) {
		 	if (curIndex>0) a.Sep(VALUE_SEPARATOR_CHAR);
		 	io1Value(a,curIndex);
			if (curIndex % 4 == 0) a.nl();
			curIndex ++;
		}
		a.TabOut();
		a.Sep(CLOSE_BRACE_CHAR);
		}

	}

    return TRUE;
}