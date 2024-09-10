/* Function to display source in the source window.  */
enum tui_status
tui_set_source_content (struct symtab *s,
                        int line_no,
                        int noerror)
{
    enum tui_status ret = TUI_FAILURE;

    if (s != (struct symtab *) NULL && s->filename != (char *) NULL)
    {
        FILE *stream;
        int i, desc, c, line_width, nlines;
        char *src_line = 0;

        if ((ret = tui_alloc_source_buffer (TUI_SRC_WIN)) == TUI_SUCCESS)
        {
            line_width = TUI_SRC_WIN->generic.width - 1;
            /* Take hilite (window border) into account, when
               calculating the number of lines.  */
            nlines = (line_no + (TUI_SRC_WIN->generic.height - 2)) - line_no;
            desc = open_source_file (s);
            if (desc < 0)
            {
                if (!noerror)
                {
                    char *name = alloca (strlen (s->filename) + 100);
                    sprintf (name, "%s:%d", s->filename, line_no);
                    print_sys_errmsg (name, errno);
                }
                ret = TUI_FAILURE;
            }
            else
            {
                if (s->line_charpos == 0)
                    find_source_lines (s, desc);

                if (line_no < 1 || line_no > s->nlines)
                {
                    close (desc);
                    printf_unfiltered (
                        "Line number %d out of range; %s has %d lines.\n",
                        line_no, s->filename, s->nlines);
                }
                else if (lseek (desc, s->line_charpos[line_no - 1], 0) < 0)
                {
                    close (desc);
                    perror_with_name (s->filename);
                }
                else
                {
                    int offset, cur_line_no, cur_line, cur_len, threshold;
                    struct tui_gen_win_info *locator = tui_locator_win_info_ptr ();
                    struct tui_source_info *src = &TUI_SRC_WIN->detail.source_info;

                    if (TUI_SRC_WIN->generic.title)
                        xfree (TUI_SRC_WIN->generic.title);
                    TUI_SRC_WIN->generic.title = xstrdup (s->filename);

                    if (src->filename)
                        xfree (src->filename);
                    src->filename = xstrdup (s->filename);

                    /* Determine the threshold for the length of the
                               line and the offset to start the display.  */
                    offset = src->horizontal_offset;
                    threshold = (line_width - 1) + offset;
                    stream = fdopen (desc, FOPEN_RT);
                    clearerr (stream);
                    cur_line = 0;
                    src->gdbarch = get_objfile_arch (s->objfile);
                    src->start_line_or_addr.loa = LOA_LINE;
                    cur_line_no = src->start_line_or_addr.u.line_no = line_no;
                    if (offset > 0)
                        src_line = (char *) xmalloc (
                                       (threshold + 1) * sizeof (char));
                    while (cur_line < nlines)
                    {
                        struct tui_win_element *element = (struct tui_win_element *)
                                                          TUI_SRC_WIN->generic.content[cur_line];

                        /* Get the first character in the line.  */
                        c = fgetc (stream);

                        if (offset == 0)
                            src_line = ((struct tui_win_element *)
                                        TUI_SRC_WIN->generic.content[
                                            cur_line])->which_element.source.line;
                        /* Init the line with the line number.  */
                        sprintf (src_line, "%-6d", cur_line_no);
                        cur_len = strlen (src_line);
                        i = cur_len -
                            ((cur_len / tui_default_tab_len ()) * tui_default_tab_len ());
                        while (i < tui_default_tab_len ())
                        {
                            src_line[cur_len] = ' ';
                            i++;
                            cur_len++;
                        }
                        src_line[cur_len] = (char) 0;

                        /* Set whether element is the execution point
                           and whether there is a break point on it.  */
                        element->which_element.source.line_or_addr.loa =
                            LOA_LINE;
                        element->which_element.source.line_or_addr.u.line_no =
                            cur_line_no;
                        element->which_element.source.is_exec_point =
                            (strcmp (((struct tui_win_element *)
                                      locator->content[0])->which_element.locator.file_name,
                                     s->filename) == 0
                             && cur_line_no == ((struct tui_win_element *)
                                                locator->content[0])->which_element.locator.line_no);
                        if (c != EOF)
                        {
                            i = strlen (src_line) - 1;
                            do
                            {
                                if ((c != '\n') && (c != '\r')
                                        && (++i < threshold))
                                {
                                    if (c < 040 && c != '\t')
                                    {
                                        src_line[i++] = '^';
                                        src_line[i] = c + 0100;
                                    }
                                    else if (c == 0177)
                                    {
                                        src_line[i++] = '^';
                                        src_line[i] = '?';
                                    }
                                    else
                                    {   /* Store the charcter in the
                                        line buffer.  If it is a tab,
                                         then translate to the correct
                                         number of chars so we don't
                                         overwrite our buffer.  */
                                        if (c == '\t')
                                        {
                                            int j, max_tab_len = tui_default_tab_len ();

                                            for (j = i - ((i / max_tab_len) * max_tab_len);
                                                    j < max_tab_len
                                                    && i < threshold;
                                                    i++, j++)
                                                src_line[i] = ' ';
                                            i--;
                                        }
                                        else
                                            src_line[i] = c;
                                    }
                                    src_line[i + 1] = 0;
                                }
                                else
                                {   /* If we have not reached EOL, then
                                       eat chars until we do.  */
                                    while (c != EOF && c != '\n' && c != '\r')
                                        c = fgetc (stream);
                                    /* Handle non-'\n' end-of-line.  */
                                    if (c == '\r'
                                            && (c = fgetc (stream)) != '\n'
                                            && c != EOF)
                                    {
                                        ungetc (c, stream);
                                        c = '\r';
                                    }

                                }
                            }
                            while (c != EOF && c != '\n' && c != '\r'
                                    && i < threshold
                                    && (c = fgetc (stream)));
                        }
                        /* Now copy the line taking the offset into
                        account.  */
                        if (strlen (src_line) > offset)
                            strcpy (((struct tui_win_element *) TUI_SRC_WIN->generic.content[
                                         cur_line])->which_element.source.line,
                                    &src_line[offset]);
                        else
                            ((struct tui_win_element *)
                                    TUI_SRC_WIN->generic.content[
                                        cur_line])->which_element.source.line[0] = (char) 0;
                        cur_line++;
                        cur_line_no++;
                    }
                    if (offset > 0)
                        xfree (src_line);
                    fclose (stream);
                    TUI_SRC_WIN->generic.content_size = nlines;
                    ret = TUI_SUCCESS;
                }
            }
        }
    }
    return ret;
}