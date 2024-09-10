void
appendTextLine(TextLineList *tl, Str line, int pos)
{
    TextLine *lbuf;

    if (tl->last == NULL) {
	pushTextLine(tl, newTextLine(Strdup(line), pos));
    }
    else {
	lbuf = tl->last->ptr;
	if (lbuf->line)
	    Strcat(lbuf->line, line);
	else
	    lbuf->line = line;
	lbuf->pos += pos;
    }
}