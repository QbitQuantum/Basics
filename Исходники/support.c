/*
 * read a string terminated by \r or \n in from a fd
 * 
 * Created: Sat Dec 12 06:29:58 EST 1992 by avalon 
 * Returns: 
 * 0 - EOF 
 * -1 - error on read 
 * >0 - number of bytes returned (<=num)
 * After opening a fd, it is necessary to init dgets() by calling it as
 * dgets(x,y,0); * to mark the buffer as being empty.
 * 
 * cleaned up by - Dianora aug 7 1997 *argh*
 */
int dgets(int fd, char *buf, int num)
{
    static char dgbuf[8192];
    static char *head = dgbuf, *tail = dgbuf;
    char *s, *t;
    int n, nr;

    /* Sanity checks. */
    if (head == tail)
	*head = '\0';

    if (!num) 
    {
	head = tail = dgbuf;
	*head = '\0';
	return 0;
    }

    if (num > sizeof(dgbuf) - 1)
	num = sizeof(dgbuf) - 1;

    FOREVER
    {
	if (head > dgbuf)
	{
	    for (nr = tail - head, s = head, t = dgbuf; nr > 0; nr--)
		*t++ = *s++;
	    tail = t;
	    head = dgbuf;
	}
	/* check input buffer for EOL and if present return string. */
	if (head < tail &&
	    ((s = strchr(head, '\n')) ||
	     (s = strchr(head, '\r'))) && s < tail)
	{
	    n = MIN(s - head + 1, num);	/* at least 1 byte */
	    memcpy(buf, head, n);
	    head += n;
	    if (head == tail)
		head = tail = dgbuf;
	    return n;
	}
	
	if (tail - head >= num) 
	{      /* dgets buf is big enough */
	    n = num;
	    memcpy(buf, head, n);
	    head += n;
	    if (head == tail)
		head = tail = dgbuf;
	    return n;
	}
	
	n = sizeof(dgbuf) - (tail - dgbuf) - 1;
	nr = read(fd, tail, n);
	if (nr == -1)
	{
	    head = tail = dgbuf;
	    return -1;
	}
	
	if (!nr)
	{
	    if (tail > head)
	    {
		n = MIN(tail - head, num);
		memcpy(buf, head, n);
		head += n;
		if (head == tail)
		    head = tail = dgbuf;
		return n;
	    }
	    head = tail = dgbuf;
	    return 0;
	}
	
	tail += nr;
	*tail = '\0';
	
	for (t = head; (s = strchr(t, '\n'));)
	{
	    if ((s > head) && (s > dgbuf))
	    {
		t = s - 1;
		for (nr = 0; *t == '\\'; nr++)
		    t--;
		if (nr & 1)
		{
		    t = s + 1;
		    s--;
		    nr = tail - t;
		    while (nr--)
			*s++ = *t++;
		    tail -= 2;
		    *tail = '\0';
		    }
		else
		    s++;
	    }
	    else
		s++;
	    t = s;
	}
	*tail = '\0';
    }
}