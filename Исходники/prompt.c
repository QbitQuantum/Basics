static void prompt_onKey(ToxWindow *self, Tox *m, wint_t key)
{
    PromptBuf *prt = self->promptbuf;

    int x, y, y2, x2;
    getyx(self->window, y, x);
    getmaxyx(self->window, y2, x2);

    /* BACKSPACE key: Remove one character from line */
    if (key == 0x107 || key == 0x8 || key == 0x7f) {
        if (prt->pos > 0) {
            del_char_buf_bck(prt->line, &prt->pos, &prt->len);
            wmove(self->window, y, x-1);    /* not necessary but fixes a display glitch */
            prt->scroll = false;
        } else {
            beep();
        }
    }

    else if (key == KEY_DC) {      /* DEL key: Remove character at pos */
        if (prt->pos != prt->len) {
            del_char_buf_frnt(prt->line, &prt->pos, &prt->len);
            prt->scroll = false;
        } else {
            beep();
        }
    }

    else if (key == T_KEY_DISCARD) {    /* CTRL-U: Delete entire line behind pos */
        if (prt->pos > 0) {
            wmove(self->window, prt->orig_y, X_OFST);
            wclrtobot(self->window);
            discard_buf(prt->line, &prt->pos, &prt->len);
        } else {
            beep();
        }
    }

    else if (key == T_KEY_KILL) {    /* CTRL-K: Delete entire line in front of pos */
        if (prt->len != prt->pos)
            kill_buf(prt->line, &prt->pos, &prt->len);
        else
            beep();
    }

    else if (key == KEY_HOME || key == T_KEY_C_A) {  /* HOME/C-a key: Move cursor to start of line */
        if (prt->pos != 0)
            prt->pos = 0;
    }

    else if (key == KEY_END || key == T_KEY_C_E) {   /* END/C-e key: move cursor to end of line */
        if (prt->pos != prt->len)
            prt->pos = prt->len;
    }

    else if (key == KEY_LEFT) {
        if (prt->pos > 0)
            --prt->pos;
        else
            beep();
    } 

    else if (key == KEY_RIGHT) {
        if (prt->pos < prt->len)
            ++prt->pos;
        else 
            beep();
    } 

    else if (key == KEY_UP) {     /* fetches previous item in history */
        wmove(self->window, prt->orig_y, X_OFST);
        fetch_hist_item(prt->line, &prt->pos, &prt->len, prt->ln_history, prt->hst_tot,
                        &prt->hst_pos, LN_HIST_MV_UP);

        /* adjust line y origin appropriately when window scrolls down */
        if (prt->at_bottom && prt->len >= x2 - X_OFST) {
            int px2 = prt->len >= x2 ? x2 : x2 - X_OFST;
            int p_ofst = px2 != x2 ? 0 : X_OFST;

            if (px2 <= 0)
                return;

            int k = prt->orig_y + ((prt->len + p_ofst) / px2);

            if (k >= y2) {
                wprintw(self->window, "\n");
                --prt->orig_y;
            }
        }
    }

    else if (key == KEY_DOWN) {    /* fetches next item in history */
        wmove(self->window, prt->orig_y, X_OFST);
        fetch_hist_item(prt->line, &prt->pos, &prt->len, prt->ln_history, prt->hst_tot,
                        &prt->hst_pos, LN_HIST_MV_DWN);
    }

    else if (key == '\t') {    /* TAB key: completes command */
        if (prt->len > 1 && prt->line[0] == '/') {
            if (complete_line(prt->line, &prt->pos, &prt->len, glob_cmd_list, AC_NUM_GLOB_COMMANDS,
                              MAX_CMDNAME_SIZE) == -1) 
                beep();
        } else {
            beep();
        }
    }

    else
#if HAVE_WIDECHAR
    if (iswprint(key))
#else
    if (isprint(key))
#endif
    {
        if (prt->len < (MAX_STR_SIZE-1)) {
            add_char_to_buf(prt->line, &prt->pos, &prt->len, key);
            prt->scroll = true;
        }
    }
    /* RETURN key: execute command */
    else if (key == '\n') {
        wprintw(self->window, "\n");
        uint8_t line[MAX_STR_SIZE];

        if (wcs_to_mbs_buf(line, prt->line, MAX_STR_SIZE) == -1)
            memset(&line, 0, sizeof(line));

        if (!string_is_empty(line))
            add_line_to_hist(prt->line, prt->len, prt->ln_history, &prt->hst_tot, &prt->hst_pos);

        execute(self->window, self, m, line, GLOBAL_COMMAND_MODE);
        reset_buf(prt->line, &prt->pos, &prt->len);
    }
}