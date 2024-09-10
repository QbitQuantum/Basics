/*
 * Process one message from message packet.
 *
 *  0   - no more messages
 *  1   - more messages
 *  2   - bad file
 *  3   - bad message header
 *  4   - unable to open temp file
 *  5   - unexpected end of packet
 *  >10 - import error
 */
int getmessage(FILE *pkt, faddr *p_from, faddr *p_to)
{
    char	    buf[MAX_LINE_LENGTH +1], *orig = NULL, *p, *l, *r, *subj = NULL;
    int		    tmp, rc, maxrc = 0, result, flags, cost;
    static faddr    f, t;
    faddr	    *o;
    time_t	    mdate = 0L;
    FILE	    *fp;
    unsigned char   buffer[0x0e];

    Nopper();

    result = fread(&buffer, 1, sizeof(buffer), pkt);
    if (result == 0) {
	Syslog('m', "Zero bytes message, assume end of pkt");
	return 0;
    }

    switch (tmp = (buffer[0x01] << 8) + buffer[0x00]) {
	case 0:	if (result == 2)
		    return 0;
		else {
		    Syslog('!', "Junk after logical end of packet, skipped");
		    return 5;

		}
	case 2:	break;

	default:Syslog('!', "bad message type: 0x%04x",tmp);
		return 2;
    }

    if (result != 14) {
	Syslog('!', "Unexpected end of packet");
	return 5;
    }

    memset(&f, 0, sizeof(f));
    memset(&t, 0, sizeof(t));
    f.node = (buffer[0x03] << 8) + buffer[0x02];
    t.node = (buffer[0x05] << 8) + buffer[0x04];
    f.net  = (buffer[0x07] << 8) + buffer[0x06];
    t.net  = (buffer[0x09] << 8) + buffer[0x08];
    flags  = (buffer[0x0b] << 8) + buffer[0x0a];
    cost   = (buffer[0x0d] << 8) + buffer[0x0c];

    /*
     * Read the DateTime, toUserName, fromUserName and subject fields
     * from the packed message. The stringlength is +1 for the right
     * check. This is different then in ifmail's original code.
     */
    if (aread(buf, sizeof(buf)-1, pkt)) {
	if (strlen(buf) > 20)
	    Syslog('!', "date too long (%d) \"%s\"", strlen(buf), printable(buf, 0));
	mdate = parsefdate(buf, NULL);
	if (aread(buf, sizeof(buf)-1, pkt)) {
	    Syslog('!', "date not null-terminated: \"%s\"",buf);
	    return 3;
	}
    }

    if (aread(buf, sizeof(buf)-1, pkt)) {
	if (strlen(buf) > 36)
	    Syslog('!', "to name too long (%d) \"%s\"", strlen(buf), printable(buf, 0));
	t.name = xstrcpy(buf);
	if (aread(buf, sizeof(buf)-1, pkt)) {
	    if (*(p=t.name+strlen(t.name)-1) == '\n')
		*p = '\0';
	    Syslog('!', "to name not null-terminated: \"%s\"",buf);
	    return 3;
	}
    }

    if (aread(buf, sizeof(buf)-1, pkt)) {
	if (strlen(buf) > 36)
	    Syslog('!', "from name too long (%d) \"%s\"", strlen(buf), printable(buf, 0));
	f.name = xstrcpy(buf);
	if (aread(buf, sizeof(buf)-1, pkt)) {
	    if (*(p=f.name+strlen(f.name)-1) == '\n') 
		*p = '\0';
	    Syslog('!', "from name not null-terminated: \"%s\"",buf);
	    return 3;
	}
    }
	
    if (aread(buf, sizeof(buf)-1, pkt)) {
	if (strlen(buf) > 72)
	    Syslog('!', "subject too long (%d) \"%s\"", strlen(buf), printable(buf, 0));
	subj = xstrcpy(buf);
	if (aread(buf, sizeof(buf)-1, pkt)) {
	    if (*(p=subj+strlen(subj)-1) == '\n') 
		*p = '\0';
	    subj = xstrcat(subj,(char *)"\\n");
	    subj = xstrcat(subj,buf);
	    Syslog('!', "subj not null-terminated: \"%s\"",buf);
	    return 3;
	}
    }

    if (feof(pkt) || ferror(pkt)) {
	Syslog('!', "Could not read message header, aborting");
	return 3;
    }

    if ((fp = tmpfile()) == NULL) {
	WriteError("$unable to open temporary file");
	return 4;
    }

    /*
     * Read the text from the .pkt file
     */
    while (aread(buf,sizeof(buf)-1,pkt)) {

	fputs(buf, fp);

	/*
	 * Extract info from Origin line if found.
	 */
	if (!strncmp(buf," * Origin:",10)) {
	    p=buf+10;
	    while (*p == ' ') 
		p++;
	    if ((l=strrchr(p,'(')) && (r=strrchr(p,')')) && (l < r)) {
		*l = '\0';
		*r = '\0';
		l++;
		if ((o = parsefnode(l))) {
		    f.point = o->point;
		    f.node = o->node;
		    f.net = o->net;
		    f.zone = o->zone;
		    if (o->domain) 
			f.domain=o->domain;
		    o->domain=NULL;
		    tidy_faddr(o);
		}
	    } else
		if (*(l=p+strlen(p)-1) == '\n')
		    *l='\0';
		for (l=p+strlen(p)-1;*l == ' ';l--) 
		    *l='\0'; 
		orig = xstrcpy(p);
	}
    }

    rc = importmsg(p_from, &f, &t, orig, subj, mdate, flags, cost, fp, p_to->zone);
    if (rc)
	rc+=10;
    if (rc > maxrc) 
	maxrc = rc;

    fclose(fp);

    if(f.name) 
	free(f.name); 
    f.name=NULL;

    if(t.name) 
	free(t.name); 
    t.name=NULL;

    if(f.domain) 
	free(f.domain); 
    f.domain=NULL;

    if(t.domain) 
	free(t.domain); 
    t.domain=NULL;

    if (subj)
	free(subj);
    subj = NULL;

    if (orig)
	free(orig);
    orig = NULL;

    if (feof(pkt) || ferror(pkt)) {
	WriteError("Unexpected end of packet");
	return 5;
    }
    return 1;
}