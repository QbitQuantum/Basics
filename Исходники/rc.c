static Str
to_str(struct param_ptr *p)
{
    switch (p->type) {
    case P_INT:
#ifdef USE_COLOR
    case P_COLOR:
#endif
#ifdef USE_M17N
    case P_CODE:
	return Sprintf("%d", (int)(*(wc_ces *) p->varptr));
#endif
    case P_NZINT:
	return Sprintf("%d", *(int *)p->varptr);
    case P_SHORT:
	return Sprintf("%d", *(short *)p->varptr);
    case P_CHARINT:
	return Sprintf("%d", *(char *)p->varptr);
    case P_CHAR:
	return Sprintf("%c", *(char *)p->varptr);
    case P_STRING:
#if defined(USE_SSL) && defined(USE_SSL_VERIFY)
    case P_SSLPATH:
#endif
	/*  SystemCharset -> InnerCharset */
	return Strnew_charp(conv_from_system(*(char **)p->varptr));
    case P_PIXELS:
    case P_SCALE:
	return Sprintf("%g", *(double *)p->varptr);
    }
    /* not reached */
    return NULL;
}