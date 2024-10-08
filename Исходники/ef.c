void editor (char *filename, int startpos)
{
    int stop    = FALSE; // exit main loop?
    int fline   = 0;     // no. of first displayed line
    int cline   = 0;     // no. of line with cursor
    int shift   = 0;     // shift to the right
    int ccol    = 0;     // column of the cursor position in the file window

    int        k, i, ndisp, rc, reply;
    char       *p, buf[1024];

    if (editor_open_file (filename) < 0) return;
    cline = min1 (startpos, nl-1);
    fline = max1 (0, cline - video_vsize()/2);

    // enter the loop
    while (1)
    {
        if (stop)
        {
            rc = 0;
            if (changed)
            {
                rc = -1;
                reply = fly_ask (0, "   Save file `%s'?   ", " Yes \n No \n Cancel ", filename);
                if (reply == 1) rc = editor_save_file (filename);
                if (reply == 2) rc = 0;
                if (reply == 3) stop = FALSE;
            }
            if (rc == 0) break;
        }
        
        ndisp = video_vsize()-1;
        // draw the screen
        for (i=0; i<ndisp; i++)
        {
            video_put_n_cell (' ', _BackWhite+_Black, video_hsize(), i, 0);
            if (i+fline < nl)
                editor_display_line (i, fline+i, shift);
        }
        video_put_n_cell (' ', _BackBlue+_White, video_hsize(), video_vsize()-1, 0);
        snprintf1 (buf, sizeof(buf), "L%d:C%d:S%d %c %s%s", cline, ccol, shift, fl_sym.v,
                 changed ? "*" : "", filename);
        video_put (buf, video_vsize()-1, 0);
        video_set_cursor (cline-fline, ccol-shift);
        video_update (0);

        // get a keyboard/mouse event and process it
        k = getmessage (-1);
        if (IS_KEY(k))
        {
            switch (k)
            {
                // Navigation keys
                
            case _Up:
            case _Down:
            case _PgUp:
            case _PgDn:
                fly_scroll_it (k, &fline, &cline, nl, video_vsize()-1);
                break;

            case _Right:
                ccol++;
                if (ccol-shift > video_hsize()-1) shift = ccol-video_hsize()+1;
                break;

            case _Left:
                ccol = max1 (ccol-1, 0);
                if (ccol < shift) shift = ccol;
                break;

            case _Home:
                ccol = 0; shift = 0;
                break;

            case _End:
                ccol = strlen(lines[cline]);
                if (ccol-shift > video_hsize()-1) shift = ccol-video_hsize()+1;
                break;

            case _CtrlHome:
                fline = 0; cline = 0; ccol = 0; shift = 0; break;

            case _CtrlEnd:
                fline = max1 (0, nl-video_vsize()+1);
                cline = min1 (fline+video_vsize()-1, nl-1);
                shift = 0;
                ccol = 0;
                break;

                // Action keys

            case _CtrlY:
                put_clipboard (lines[cline]);
                free (lines[cline]);
                for (i=cline; i<nl-1; i++)
                    lines[i] = lines[i+1];
                nl--;
                changed = TRUE;
                break;

            case _ShiftInsert:
            case _CtrlV:
                p = get_clipboard ();
                if (p == NULL || *p == '\0') break;
                if (nl == na)
                {
                    na *= 2;
                    lines = realloc (lines, sizeof(char *) * na);
                }
                for (i=nl-1; i>cline; i--)
                    lines[i+1] = lines[i];
                lines[cline+1] = p;
                ccol = 0;
                shift = 0;
                cline++;
                if (cline-fline == video_vsize()-1) fline++;
                nl++;
                changed = TRUE;
                break;

            case _BackSpace:
                if (ccol == 0)
                {
                    // ccol == 0: glue this line to the previous
                    if (cline == 0) break;
                    p = malloc (strlen (lines[cline])+strlen(lines[cline-1])+1);
                    strcpy (p, lines[cline-1]);
                    strcat (p, lines[cline]);
                    ccol = strlen (lines[cline-1]);
                    if (ccol-shift > video_hsize()-1) shift = ccol-video_hsize()+1;
                    free (lines[cline-1]);
                    free (lines[cline]);
                    lines[cline-1] = p;
                    for (i=cline; i<nl-1; i++)
                        lines[i] = lines[i+1];
                    cline--;
                    nl--;
                }
                else
                {
                    // ccol != 0: delete char at ccol-1, move cursor left
                    str_delete (lines[cline], lines[cline]+ccol-1);
                    ccol--;
                    if (ccol < shift) shift = ccol;
                }
                changed = TRUE;
                break;

            case _Enter:
                if (nl == na)
                {
                    na *= 2;
                    lines = realloc (lines, sizeof(char *) * na);
                }
                for (i=nl-1; i>cline; i--)
                    lines[i+1] = lines[i];
                if (ccol < strlen (lines[cline]))
                {
                    lines[cline+1] = strdup (lines[cline]+ccol);
                    lines[cline][ccol] = '\0';
                }
                else
                {
                    lines[cline+1] = strdup ("");
                }
                ccol = 0;
                shift = 0;
                cline++;
                if (cline-fline == video_vsize()-1) fline++;
                nl++;
                changed = TRUE;
                break;

            case _Delete:
                if (ccol >= strlen (lines[cline]))
                {
                    // glue previous line to this one
                    if (cline == nl-1) break;
                    p = malloc (ccol+strlen(lines[cline+1])+1);
                    strcpy (p, lines[cline]);
                    memset (p+strlen(lines[cline]), ' ', ccol-strlen(lines[cline]));
                    strcpy (p+ccol, lines[cline+1]);
                    free (lines[cline]);
                    free (lines[cline+1]);
                    lines[cline] = p;
                    for (i=cline+1; i<nl-1; i++)
                        lines[i] = lines[i+1];
                    nl--;
                }
                else
                {
                    // ccol != 0: delete char at ccol-1, move cursor left
                    str_delete (lines[cline], lines[cline]+ccol);
                }
                changed = TRUE;
                break;

            case _F2:
                rc = editor_save_file (filename);
                if (rc == 0) changed = FALSE;
                break;
                
            case _Esc:
            case _F10:
                stop = TRUE; break;

                // character keys
                
            default:
                if (k >= ' ' && k <= 255)
                {
                    str_insert_at (cline, k, ccol);
                    ccol++;
                    changed = TRUE;
                }
            }
        }
        else if (IS_MOUSE(k))
        {
        }
        else if (IS_SYSTEM(k))
        {
            switch (SYS_TYPE(k))
            {
            case SYSTEM_QUIT:
                stop = TRUE; break;
            }
        }
    }

    if (nl != 0 && lines != NULL)
        for (i=0; i<nl; i++)
            free (lines[i]);
    if (na != 0 && lines != NULL) free (lines);
    na = 0;
    lines = NULL;
}