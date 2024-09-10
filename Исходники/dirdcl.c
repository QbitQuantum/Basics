void dirdcl(void)
{
    int type;

    if (tokentype == '(') { /* (dcl) */
        dcl();
        if (tokentype != ')') {
            errmsg("error: missing )\n");
        }
    } else if (tokentype == NAME) { /* variable name */
        if (name[0] == '\0') {
            strncpy(name, token, MAXTOKEN);
        }
    }
    else {
        prevtoken = YES;
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS ||
            type == '(') {
        if (type == PARENS) {
            strncat(out, " function returning",
                    MAXTOKEN - strlen(out) - 1);
        }
        else if (type == '(') {
            strncat(out, " function expecting", 
                    MAXTOKEN - strlen(out) - 1);
            parmdcl();
            strncat(out, " and returning", 
                    MAXTOKEN - strlen(out) - 1);
        }
        else {
            strncat(out, " array", MAXTOKEN - strlen(out) - 1);
            strncat(out, token, MAXTOKEN - strlen(out) - 1);
            strncat(out, " of", MAXTOKEN - strlen(out));
        }
    }
}