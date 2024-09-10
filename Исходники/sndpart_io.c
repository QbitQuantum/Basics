static int do_emit_mimepart_body(FILE *fp_dest, SEND_BODYPART *part)
{
    char *fname_tmp, *fname_sel, cmd_buf[SLEN], *s;
    int rc, i;
    FILE *fp_src;

    rc = -1;
    fp_src = NULL;

    switch (mime_encoding_type(part->content_header[BP_CONT_ENCODING])) {

    case ENCODING_QUOTED:
	if ((fname_tmp = tempnam(temp_dir, "emm.")) == NULL) {
	    show_error("Cannot make temp file name.");
	    return -1;
	}
	MIME_ENCODE_CMD_QUOTED(cmd_buf, part->fname, fname_tmp);
	break;

    case ENCODING_BASE64:
	if ((fname_tmp = tempnam(temp_dir, "emm.")) == NULL) {
	    show_error("Cannot make temp file name.");
	    return -1;
	}
	MIME_ENCODE_CMD_BASE64(cmd_buf, part->fname, fname_tmp);
	break;

    case ENCODING_UUENCODE:
	if ((fname_tmp = tempnam(temp_dir, "emm.")) == NULL) {
	    show_error("Cannot make temp file name.");
	    return -1;
	}
	MIME_ENCODE_CMD_UUENCODE(cmd_buf, part->fname, fname_tmp);
	break;

    default:
	/* encoding not needed */
	fname_tmp = NULL;
	break;
    }

    if (fname_tmp == NULL) {
	fname_sel = part->fname;
    } else if ((i =  system_call(cmd_buf, 0)) == 0) {
	fname_sel = fname_tmp;
    } else {
	for (s = cmd_buf ; *s != '\0' && !isspace(*s) ; ++s)
	    ;
	*s = '\0';
	s = (cmd_buf[0] != '\0' ? basename(cmd_buf) : "encoder");
	show_error("Cannot encode \"%s\".  (\"%s\" exit status %d)",
		    basename(part->fname), s, i);
	goto done;
    }

    if ((fp_src = file_open(fname_sel, "r")) == NULL)
	goto done;
    if (file_copy(fp_src, fp_dest, fname_sel, "message body") < 0)
	goto done;
    if (file_close(fp_src, fname_sel) < 0)
	goto done;
    else 
        fp_src = NULL;

    rc = 0;

done:
    if (fp_src != NULL)
	(void) fclose(fp_src);
    if (fname_tmp != NULL) {
	(void) unlink(fname_tmp);
	free((malloc_t)fname_tmp);
    }
    return rc;
}