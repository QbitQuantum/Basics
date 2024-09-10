void
clip_mch_set_selection(VimClipboard *cbd)
{
    int type;
    long_u  len;
    char_u *text_clip, vim_clip[2], *str = NULL;
    PhClipHeader clip_header[2];

    /* Prevent recursion from clip_get_selection() */
    if (cbd->owned == TRUE)
	return;

    cbd->owned = TRUE;
    clip_get_selection(cbd);
    cbd->owned = FALSE;

    type = clip_convert_selection(&str, &len, cbd);
    if (type >= 0)
    {
	text_clip = lalloc(len + 1, TRUE); /* Normal text */

	if (text_clip && vim_clip)
	{
	    memset(clip_header, 0, sizeof(clip_header));

	    STRNCPY(clip_header[0].type, CLIP_TYPE_VIM, 8);
	    clip_header[0].length = sizeof(vim_clip);
	    clip_header[0].data   = vim_clip;

	    STRNCPY(clip_header[1].type, CLIP_TYPE_TEXT, 8);
	    clip_header[1].length = len + 1;
	    clip_header[1].data   = text_clip;

	    switch(type)
	    {
		default: /* fallthrough to MLINE */
		case MLINE:	*vim_clip = 'L'; break;
		case MCHAR:	*vim_clip = 'C'; break;
		case MBLOCK:	*vim_clip = 'B'; break;
	    }

	    vim_strncpy(text_clip, str, len);

	    vim_clip[ 1 ] = NUL;

	    PhClipboardCopy(PhInputGroup(NULL), 2, clip_header);
	}
	vim_free(text_clip);
    }
    vim_free(str);
}