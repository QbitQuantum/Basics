static int send_msg(process *pp, int act, const char *fmt, ...)
   {int nl;
    char msg[BFLRG];
    char *p;
    dbgrsp *gr;
    atdbgdes *st;

    VA_START(fmt);

    if (fmt == NULL)
       p = NULL;
    else
       {VSNPRINTF(msg, BFLRG, fmt);
	p  = msg;};

    VA_END;

    gr = (dbgrsp *) pp->a;
    st = gr->st;
    gr->action = act;

/* log the message sent */
    if ((st->log != NULL) && (p != NULL))
       fprintf(st->log, "SND: %s\n", p);

    nl = job_response(pp, 30000, p);

    return(nl);}