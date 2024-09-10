PRIVATE void HTMIME_put_character ARGS2(HTStream *, me, char, c)
{
    if (me->state == MIME_TRANSPARENT) {
    	(*me->targetClass.put_character)(me->target, c);/* MUST BE FAST */
	return;
    }
    
    /* This slightly simple conversion just strips CR and turns LF to
    ** newline. On unix LF is \n but on Mac \n is CR for example.
    ** See NetToText for an implementation which preserves single CR or LF.
    */
    if (me->net_ascii) {
        c = FROMASCII(c);
	if (c == CR) return;
	else if (c == LF) c = '\n';
    }
    
    switch(me->state) {

    case MIME_IGNORE:
    	return;

    case MIME_TRANSPARENT:		/* Not reached see above */
    	(*me->targetClass.put_character)(me->target, c);
	return;
	
    case MIME_NET_ASCII:
    	(*me->targetClass.put_character)(me->target, c); /* MUST BE FAST */
	return;

    case NEWLINE:
	if (c != '\n' && WHITE(c)) {		/* Folded line */
	    me->state = me->fold_state;	/* pop state before newline */
	    break;
	}
	
	/*	else Falls through */
	
    case BEGINNING_OF_LINE:
        switch(c) {
	case 'c':
	case 'C':
	    me->check_pointer = "ontent-t";
	    me->if_ok = CONTENT_T;
	    me->state = CHECK;
	    break;
	case '\n':			/* Blank line: End of Header! */
	    {
	        if (TRACE) fprintf(stderr,
			"HTMIME: MIME content type is %s, converting to %s\n",
			HTAtom_name(me->format), HTAtom_name(me->targetRep));
		me->target = HTStreamStack(me->format, me->request, NO);
		if (!me->target) {
		    if (TRACE) fprintf(stderr, "MIME: Can't translate! ** \n");
		    me->target = me->sink;	/* Cheat */
		}
		if (me->target) {
		    me->targetClass = *me->target->isa;
		/* Check for encoding and select state from there @@ */
		
		    me->state = MIME_TRANSPARENT; /* From now push straigh through */
		} else {
		    me->state = MIME_IGNORE;		/* What else to do? */
		}
	    }
	    break;
	    
	default:
	   goto bad_field_name;
	   break;
	   
	} /* switch on character */
        break;
	
    case CHECK:				/* Check against string */
        if (TOLOWER(c) == *(me->check_pointer)++) {
	    if (!*me->check_pointer) me->state = me->if_ok;
	} else {		/* Error */
	    if (TRACE) fprintf(stderr,
	    	"HTMIME: Bad character `%c' found where `%s' expected\n",
		c, me->check_pointer - 1);
	    goto bad_field_name;
	}
	break;
	
    case CONTENT_T:
        switch(c) {
	case 'r':
	case 'R':
	    me->check_pointer = "ansfer-encoding:";
	    me->if_ok = CONTENT_TRANSFER_ENCODING;
	    me->state = CHECK;
	    break;
	    
	case 'y':
	case 'Y':
	    me->check_pointer = "pe:";
	    me->if_ok = CONTENT_TYPE;
	    me->state = CHECK;
	    break;
	    
	default:
	    goto bad_field_name;
	    
	} /* switch on character */
	break;
	
    case CONTENT_TYPE:
    case CONTENT_TRANSFER_ENCODING:
        me->field = me->state;		/* remember it */
	me->state = SKIP_GET_VALUE;
				/* Fall through! */
    case SKIP_GET_VALUE:
    	if (c == '\n') {
	   me->fold_state = me->state;
	   me->state = NEWLINE;
	   break;
	}
	if (WHITE(c)) break;	/* Skip white space */
	
	me->value_pointer = me->value;
	me->state = GET_VALUE;   
	/* Fall through to store first character */
	
    case GET_VALUE:
    	if (WHITE(c)) {			/* End of field */
	    *me->value_pointer = 0;
	    switch (me->field) {
	    case CONTENT_TYPE:
	        me->format = HTAtom_for(me->value);
		break;
	    case CONTENT_TRANSFER_ENCODING:
	        me->encoding = HTAtom_for(me->value);
		break;
	    default:		/* Should never get here */
	    	break;
	    }
	} else {
	    if (me->value_pointer < me->value + VALUE_SIZE - 1) {
	        *me->value_pointer++ = c;
		break;
	    } else {
	        goto value_too_long;
	    }
	}
	/* Fall through */
	
    case JUNK_LINE:
        if (c == '\n') {
	    me->state = NEWLINE;
	    me->fold_state = me->state;
	}
	break;
	
	
    } /* switch on state*/
    
    return;
    
value_too_long:
    if (TRACE) fprintf(stderr,
    	"HTMIME: *** Syntax error. (string too long)\n");
    
bad_field_name:				/* Ignore it */
    me->state = JUNK_LINE;
    return;
    
}