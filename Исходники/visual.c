R_API int r_core_visual_cmd(RCore *core, int ch) {
    RAsmOp op;
    ut64 offset = core->offset;
    char buf[4096];
    int i, ret, offscreen, cols = core->print->cols, delta = 0;
    ch = r_cons_arrow_to_hjkl (ch);
    ch = visual_nkey (core, ch);
    if (ch<2) return 1;

    // do we need hotkeys for data references? not only calls?
    if (ch>='0'&& ch<='9') {
        ut64 off = core->asmqjmps[ch-'0'];
        if (off != UT64_MAX) {
            int delta = R_ABS ((st64)off-(st64)offset);
            r_io_sundo_push (core->io, offset);
            if (curset && delta<100) {
                cursor = delta;
            } else {
                r_core_visual_seek_animation (core, off);
                //r_core_seek (core, off, 1);
            }
            r_core_block_read (core, 1);
        }
    } else
        switch (ch) {
        case 0x0d:
        {
            r_cons_enable_mouse (R_TRUE);
            RAnalOp *op = r_core_anal_op (core, core->offset+cursor);
            if (op) {
                if (op->type == R_ANAL_OP_TYPE_JMP	||
                        op->type == R_ANAL_OP_TYPE_CJMP ||
                        op->type == R_ANAL_OP_TYPE_CALL) {
                    r_io_sundo_push (core->io, offset);
                    r_core_visual_seek_animation(core, op->jump);
                }
            }
            r_anal_op_free (op);
        }
        break;
        case 90: // shift+tab
            if (!strcmp (printfmt[0], "x"))
                printfmt[0] = "pxa";
            else printfmt[0] = "x";
            break;
        case 9: // tab
        {   // XXX: unify diff mode detection
            ut64 f = r_config_get_i (core->config, "diff.from");
            ut64 t = r_config_get_i (core->config, "diff.to");
            if (f == t && f == 0) {
                core->print->col = core->print->col==1? 2: 1;
            } else {
                ut64 delta = offset - f;
                r_core_seek (core, t+delta, 1);
                r_config_set_i (core->config, "diff.from", t);
                r_config_set_i (core->config, "diff.to", f);
            }
        }
        break;
        case 'a':
            if (core->file && !(core->file->rwx & 2)) {
                r_cons_printf ("\nFile has been opened in read-only mode. Use -w flag\n");
                r_cons_any_key ();
                return R_TRUE;
            }
            r_cons_printf ("Enter assembler opcodes separated with ';':\n");
            showcursor (core, R_TRUE);
            r_cons_flush ();
            r_cons_set_raw (R_FALSE);
            strcpy (buf, "wa ");
            r_line_set_prompt (":> ");
            if (r_cons_fgets (buf+3, 1000, 0, NULL) <0) buf[0]='\0';
            if (*buf) {
                if (curset) r_core_seek (core, core->offset + cursor, 0);
                r_core_cmd (core, buf, R_TRUE);
                if (curset) r_core_seek (core, core->offset - cursor, 1);
            }
            showcursor (core, R_FALSE);
            r_cons_set_raw (R_TRUE);
            break;
        case '!':
            r_cons_2048();
            break;
        case 'o':
            visual_offset (core);
            break;
        case 'A':
        {   int oc = curset;
            ut64 off = curset? core->offset+cursor : core->offset;
            curset = 0;
            r_core_visual_asm (core, off);
            curset = oc;
        }
        break;
        case 'c':
            setcursor (core, curset?0:1);
            break;
        case 'C':
            color = color? 0: 1;
            r_config_set_i (core->config, "scr.color", color);
            break;
        case 'd':
            r_core_visual_define (core);
            break;
        case 'D':
            setdiff (core);
            break;
        case 'f':
        {
            int range, min, max;
            char name[256], *n;
            r_line_set_prompt ("flag name: ");
            showcursor (core, R_TRUE);
            if (r_cons_fgets (name, sizeof (name), 0, NULL) >=0 && *name) {
                n = r_str_chop (name);
                if (*name=='-') {
                    if (*n) r_flag_unset (core->flags, n+1, NULL);
                } else {
                    if (ocursor != -1) {
                        min = R_MIN (cursor, ocursor);
                        max = R_MAX (cursor, ocursor);
                    } else {
                        min = max = cursor;
                    }
                    range = max-min+1;
                    if (range<1) range = 1;
                    if (*n) r_flag_set (core->flags, n,
                                            core->offset + min, range, 1);
                }
            }
        }
        showcursor (core, R_FALSE);
        break;
        case 'F':
            r_flag_unset_i (core->flags, core->offset + cursor, NULL);
            break;
        case 'n':
            r_core_seek_next (core, r_config_get (core->config, "scr.nkey"));
            break;
        case 'N':
            r_core_seek_previous (core, r_config_get (core->config, "scr.nkey"));
            break;
        case 'i':
        case 'I':
            if (core->file && !(core->file->rwx & 2)) {
                r_cons_printf ("\nFile has been opened in read-only mode. Use -w flag\n");
                r_cons_any_key ();
                return R_TRUE;
            }
            showcursor (core, R_TRUE);
            r_cons_flush ();
            r_cons_set_raw (0);
            if (ch=='I') {
                strcpy (buf, "wow ");
                r_line_set_prompt ("insert hexpair block: ");
                if (r_cons_fgets (buf+4, sizeof (buf)-5, 0, NULL) <0)
                    buf[0]='\0';
                char *p = strdup (buf);
                int cur = core->print->cur;
                if (cur>=core->blocksize)
                    cur = core->print->cur-1;
                snprintf (buf, sizeof (buf), "%s @ $$0!%i", p,
                          core->blocksize-cursor);
                r_core_cmd (core, buf, 0);
                free (p);
                break;
            }
            delta = (ocursor!=-1)? R_MIN (cursor, ocursor): cursor;
            if (core->print->col==2) {
                strcpy (buf, "\"w ");
                r_line_set_prompt ("insert string: ");
                if (r_cons_fgets (buf+3, sizeof (buf)-4, 0, NULL) <0)
                    buf[0]='\0';
                strcat (buf, "\"");
            } else {
                r_line_set_prompt ("insert hex: ");
                if (ocursor != -1) {
                    int bs = R_ABS (cursor-ocursor)+1;
                    core->blocksize = bs;
                    strcpy (buf, "wow ");
                } else {
                    strcpy (buf, "wx ");
                }
                if (r_cons_fgets (buf+strlen (buf), sizeof (buf)-strlen (buf), 0, NULL) <0)
                    buf[0]='\0';
            }
            if (curset) r_core_seek (core, core->offset + delta, 0);
            r_core_cmd (core, buf, 1);
            if (curset) r_core_seek (core, offset, 1);
            r_cons_set_raw (1);
            showcursor (core, R_FALSE);
            break;
        case 'R':
            r_core_cmd0 (core, "ecr");
            break;
        case 'e':
            r_core_visual_config (core);
            break;
        case 'E':
            r_core_visual_colors (core);
            break;
        case 'M':
            r_core_visual_mounts (core);
            break;
        case 't':
            r_core_visual_trackflags (core);
            break;
        case 'x':
        {
            int count = 0;
            RList *xrefs = NULL;
            RAnalRef *refi;
            RListIter *iter;
            RAnalFunction *fun;

            if ((xrefs = r_anal_xref_get (core->anal, core->offset))) {
                r_cons_gotoxy (1, 1);
                r_cons_printf ("[GOTO XREF]> \n");
                if (r_list_empty (xrefs)) {
                    r_cons_printf ("\tNo XREF found at 0x%"PFMT64x"\n", core->offset);
                    r_cons_any_key ();
                    r_cons_clear00 ();
                } else {
                    r_list_foreach (xrefs, iter, refi) {
                        fun = r_anal_fcn_find (core->anal, refi->addr, R_ANAL_FCN_TYPE_NULL);
                        r_cons_printf (" [%i] 0x%08"PFMT64x" %s XREF 0x%08"PFMT64x" (%s)                      \n", count,
                                       refi->at,
                                       refi->type==R_ANAL_REF_TYPE_CODE?"CODE (JMP)":
                                       refi->type==R_ANAL_REF_TYPE_CALL?"CODE (CALL)":"DATA", refi->addr,
                                       fun?fun->name:"unk");
                        if (++count > 9) break;
                    }
                }
            } else xrefs = NULL;