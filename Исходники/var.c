static void DumpSysVar(char const *name, const SysVar *v)
{
    char buffer[VAR_NAME_LEN+10];

    if (name && !*name) name=NULL;
    if (!v && !name) return;  /* Shouldn't happen... */

    buffer[0]='$'; buffer[1] = 0;
    if (name) strcat(buffer, name); else strcat(buffer, v->name);
    fprintf(ErrFp, "%*s  ", VAR_NAME_LEN+1, buffer);
    if (v) {
	if (v->type == SPECIAL_TYPE) {
	    Value val;
	    SysVarFunc f = (SysVarFunc) v->value;
	    f(0, &val);
	    PrintValue(&val, ErrFp);
	    Putc('\n', ErrFp);
	    DestroyValue(val);
	} else if (v->type == STR_TYPE) {
	    char const *s = *((char **)v->value);
	    int y;
	    Putc('"', ErrFp);
	    for (y=0; y<MAX_PRT_LEN && *s; y++) {
		if (*s == '"') {
		    fprintf(ErrFp, "\" + char(34) + \"");
		    s++;
		} else {
		    Putc(*s++, ErrFp);
		}
	    }
	    Putc('"', ErrFp);
	    if (*s) fprintf(ErrFp, "...");
	    Putc('\n', ErrFp);
	} else if (v->type == DATE_TYPE) {
	    Value val;
	    val.type = DATE_TYPE;
	    val.v.val = * (int *) v->value;
	    PrintValue(&val, ErrFp);
	    Putc('\n', ErrFp);
	} else {
	    if (!v->modifiable) fprintf(ErrFp, "%d\n", *((int *)v->value));
	    else {
		fprintf(ErrFp, "%-10d  ", *((int *)v->value));
		if (v->min == ANY) fprintf(ErrFp, "(-Inf, ");
		else                         fprintf(ErrFp, "[%d, ", v->min);
		if (v->max == ANY) fprintf(ErrFp, "Inf)\n");
		else                         fprintf(ErrFp, "%d]\n", v->max);
	    }
	}
    } else   fprintf(ErrFp, "%s\n", UNDEF);

    return;
}