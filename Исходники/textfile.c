void TextFileComp::Init() {

    /* read in the text from begstr to endstr */
    FILE* fptr = fopen(_pathname, "r");
    char *buffer;

    if (_linewidth == 0) {
	buffer = new char[1];
	buffer[0] = '\0';
	fclose (fptr);
	return;
    }
    if (!fptr) {
	buffer = new char[1];
	buffer[0] = '\0';
    } else {
	char inbuf[BUFSIZ];
        int nsub;
	buffer = new char[BUFSIZ];
	
	int bufsiz = BUFSIZ;
	int buflen = 0;

	fgets( inbuf, BUFSIZ, fptr);
	if (_begstr) 
	    while (!feof(fptr) && strncmp(_begstr, inbuf, strlen(_begstr)) != 0) 
		fgets( inbuf, BUFSIZ, fptr);

	int len;
	int nc = 0;
        int wordc = 0;
	char* wordbuf;
	char c;

	/* loop until eof or endstr is found */
	while (!feof(fptr) && (_endstr ? strncmp(_endstr, inbuf, strlen(_endstr)) != 0 : true)) {
	    len = strlen(inbuf);
            if (_linewidth > -1) 
	       nsub = len / _linewidth;
	    else 
	       nsub = 0;

	    /* double buffer length if needed */
	    if (buflen+len+nsub >= bufsiz) {
		bufsiz *= 2;
		char* newbuffer = new char[bufsiz];
		strcpy( newbuffer, buffer );
		delete buffer;
		buffer = newbuffer;
	    }

	    if (_linewidth > -1) {
		wordbuf = new char[len+nsub+1];

	        for (int i = 0; i < len; i++) {
	            c = inbuf[i];
		    ++nc;
		    if (c == ' ' || c == '\t' || c == '\n') {
			if (nc > _linewidth+1) {
			    strcpy(buffer+buflen, "\n");
	       		    ++buflen;
			    if (c == '\n' && nc > 1 ) {
			        wordbuf[wordc] = ' ';
			    } else {
			        wordbuf[wordc] = c;
                            }
			    wordbuf[wordc+1] = '\0';
			    nc = strlen(wordbuf);
			    wordc = 0;
			    strcpy(buffer+buflen, wordbuf);
	       		    buflen += strlen(wordbuf);
			
			} else {
			    if (c == '\n' && nc > 1 && i > 0) {
			        wordbuf[wordc] = ' ';
			        wordbuf[wordc+1] = '\0';
			    } else if (c == '\n' && i == 0) {
			        wordbuf[wordc] = c;
			        wordbuf[wordc+1] = c;
			        wordbuf[wordc+2] = '\0';
				nc = 0;
			    } else {
			        wordbuf[wordc] = c;
			        wordbuf[wordc+1] = '\0';
                            }
			    wordc = 0;
			    if (buffer[buflen-1] != ' ' || wordbuf[0] != ' ') {
				strcpy(buffer+buflen, wordbuf);
				buflen += strlen(wordbuf); 
			    } else {
				strcpy(buffer+buflen, wordbuf+1);
				buflen += strlen(wordbuf) - 1; 
			    }
			}
		    
		    } else {
			if (c=='\\') {
			    c = inbuf[++i];
			    if (isdigit(c)) {
				char buf[4];
				buf[0] = c; 
				buf[1] = buf[2] = buf[3] = '\0';
				if (isdigit(inbuf[i+1])) {
				    buf[1] = inbuf[++i];
				    if (isdigit(inbuf[i+1])) {
					buf[2] = inbuf[++i];
				    }
				}
				c = ParamList::octal(buf);
			    }
			} 
			wordbuf[wordc] = c;
			++wordc;
		    }
	        }
	        delete wordbuf;
	    
	    } else {
                strcpy(buffer+buflen, inbuf);
	        buflen += strlen(inbuf);
            }
	    fgets( inbuf, BUFSIZ, fptr);
	}
	/* done looping until eof or endstr is found */
    }

    fclose(fptr);

    /* setup the graphic */
    ((TextGraphic*)_gr)->SetOriginal(buffer);
    delete buffer;

    /* correct font vertical position */
    PSFont* f = _gr->GetFont();
    float sep = 1 - f->GetLineHt();
    Transformer* t = _gr->GetTransformer();
    float dx = 0., dy = sep;

    if (t != nil) {
        float x0, y0, x1, y1;
        t->Transform(0., 0., x0, y0);
        t->Transform(0., sep, x1, y1);
        dx = x1 - x0;
        dy = y1 - y0;
    }
    _gr->Translate(dx, dy);

}