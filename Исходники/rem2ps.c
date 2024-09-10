void WriteOneEntry(CalEntry *c)
{
    int ch, i;
    char const *s = c->entry;

    printf("  [");

    /* Chew up leading spaces */
    while(isspace((unsigned char) *s)) s++;

    /* Skip three decimal numbers for COLOR special */
    if (c->special == SPECIAL_COLOR) {
	for (i=0; i<3; i++) {
	    while(*s && !isspace(*s)) s++;
	    while(*s && isspace(*s)) s++;
	}
    }

    PutChar('(');
    while(*s) {
	/* Use the "unsigned char" cast to fix problem on Solaris 2.5 */
	/* which treated some latin1 characters as white space.       */
	ch = (unsigned char) *s++;
	if (ch == '\\' || ch == '(' || ch == ')') PutChar('\\');
	if (!isspace(ch)) PutChar(ch);
	else {
	    PutChar(')');
	    while(isspace((unsigned char)*s)) s++;
	    if (!*s) {
		goto finish;
	    }
	    PutChar('(');
	}
    }
    printf(")\n");
  finish:
    if (c->special == SPECIAL_COLOR) {
	int r, g, b;
	if (sscanf(c->entry, "%d %d %d", &r, &g, &b) == 3) {
	    if (r < 0) r = 0;
	    else if (r > 255) r = 255;
	    if (g < 0) g = 0;
	    else if (g > 255) g = 255;
	    if (b < 0) b = 0;
	    else if (b > 255) b = 255;
	    printf("(gsave %f %f %f setrgbcolor)(grestore)",
		   r / 255.0, g / 255.0, b / 255.0);
	} else {
	    /* Punt... unrecognized color is black */
	    printf("()()");
	}
    } else {
	printf("()()");
    }
    printf("]\n");
}