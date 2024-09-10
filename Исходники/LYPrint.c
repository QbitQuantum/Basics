static void send_file_to_file(DocInfo *newdoc,
			      char *content_base,
			      char *sug_filename)
{
    BOOLEAN FirstRecall = TRUE;
    BOOLEAN use_cte;
    const char *disp_charset;
    FILE *outfile_fp;
    bstring *buffer = NULL;
    bstring *filename = NULL;
    int FnameNum = -1;
    int FnameTotal;
    int c = 0;

    _statusline(FILENAME_PROMPT);

  retry:
    SetupFilename(&filename, sug_filename);
    if (lynx_save_space) {
	BStrCopy0(buffer, lynx_save_space);
	BStrCat(buffer, filename);
	BStrCopy(filename, buffer);
    } else {
	BStrCopy0(buffer, "");
    }

  check_recall:
    switch (RecallFilename(&filename, &FirstRecall, &FnameNum,
			   &FnameTotal, PRINT_FLAG)) {
    case FN_INIT:
	goto retry;
    case FN_READ:
	goto check_recall;
    case FN_QUIT:
	goto done;
    default:
	break;
    }

    if (!LYValidateFilename(&buffer, &filename)) {
	CancelPrint(SAVE_REQUEST_CANCELLED);
    }

    /*
     * See if it already exists.
     */
    switch (c = LYValidateOutput(buffer->str)) {
    case 'Y':
	break;
    case 'N':
	_statusline(NEW_FILENAME_PROMPT);
	FirstRecall = TRUE;
	FnameNum = FnameTotal;
	goto retry;
    default:
	goto done;
    }

    /*
     * See if we can write to it.
     */
    CTRACE((tfp, "LYPrint: filename is %s, action is `%c'\n", buffer->str, c));

#ifdef HAVE_POPEN
    if (buffer->str[0] == '|') {
	if (no_shell) {
	    HTUserMsg(SPAWNING_DISABLED);
	    FirstRecall = TRUE;
	    FnameNum = FnameTotal;
	    goto retry;
	} else if ((outfile_fp = popen(buffer->str + 1, "w")) == NULL) {
	    CTRACE((tfp, "LYPrint: errno is %d\n", errno));
	    HTAlert(CANNOT_WRITE_TO_FILE);
	    _statusline(NEW_FILENAME_PROMPT);
	    FirstRecall = TRUE;
	    FnameNum = FnameTotal;
	    goto retry;
	}
    } else
#endif
	if ((outfile_fp = (TOUPPER(c) == 'A'
			   ? LYAppendToTxtFile(buffer->str)
			   : LYNewTxtFile(buffer->str))) == NULL) {
	CTRACE((tfp, "LYPrint: errno is %d\n", errno));
	HTAlert(CANNOT_WRITE_TO_FILE);
	_statusline(NEW_FILENAME_PROMPT);
	FirstRecall = TRUE;
	FnameNum = FnameTotal;
	goto retry;
    }

    if (LYPrependBaseToSource && HTisDocumentSource()) {
	/*
	 * Added the document's base as a BASE tag to the top of the file.  May
	 * create technically invalid HTML, but will help get any partial or
	 * relative URLs resolved properly if no BASE tag is present to replace
	 * it.  - FM
	 *
	 * Add timestamp (last reload).
	 */

	fprintf(outfile_fp,
		"<!-- X-URL: %s -->\n", newdoc->address);
	if (HText_getDate() != NULL) {
	    fprintf(outfile_fp,
		    "<!-- Date: %s -->\n", HText_getDate());
	    if (HText_getLastModified() != NULL
		&& strcmp(HText_getLastModified(), HText_getDate())
		&& strcmp(HText_getLastModified(),
			  "Thu, 01 Jan 1970 00:00:01 GMT")) {
		fprintf(outfile_fp,
			"<!-- Last-Modified: %s -->\n", HText_getLastModified());
	    }
	}

	fprintf(outfile_fp,
		"<BASE HREF=\"%s\">\n", content_base);
    }

    if (LYPrependCharsetToSource && HTisDocumentSource()) {
	/*
	 * Added the document's charset as a META CHARSET tag to the top of the
	 * file.  May create technically invalid HTML, but will help to resolve
	 * properly the document converted via chartrans:  printed document
	 * correspond to a display charset and we *should* override both
	 * assume_local_charset and original document's META CHARSET (if any).
	 *
	 * Currently, if several META CHARSETs are found Lynx uses the first
	 * only, and it is opposite to BASE where the original BASE in the
	 * <HEAD> overrides ones from the top.
	 *
	 * As in print-to-email we write charset only if the document has 8-bit
	 * characters, and we have no CJK or an unofficial "x-" charset.
	 */
	use_cte = HTLoadedDocumentEightbit();
	disp_charset = LYCharSet_UC[current_char_set].MIMEname;
	if (!use_cte || LYHaveCJKCharacterSet ||
	    strncasecomp(disp_charset, "x-", 2) == 0) {
	} else {
	    fprintf(outfile_fp,
		    "<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=%s\">\n\n",
		    disp_charset);
	}
    }

    print_wwwfile_to_fd(outfile_fp, FALSE, FALSE);	/* FILE */
    if (keypad_mode)
	printlist(outfile_fp, FALSE);

#ifdef HAVE_POPEN
    if (LYIsPipeCommand(buffer->str))
	pclose(outfile_fp);
    else
#endif
	LYCloseOutput(outfile_fp);

#ifdef VMS
    if (0 == strncasecomp(buffer->str, "sys$disk:", 9)) {
	if (0 == StrNCmp((buffer->str + 9), "[]", 2)) {
	    HTAddSugFilename(buffer->str + 11);
	} else {
	    HTAddSugFilename(buffer->str + 9);
	}
    } else {
	HTAddSugFilename(buffer->str);
    }
#else
    HTAddSugFilename(buffer->str);
#endif /* VMS */

  done:
    BStrFree(buffer);
    BStrFree(filename);
    return;
}