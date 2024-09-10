/* Keys for line input in a text grid window. */
static command_t *commands_textgrid_line(window_textgrid_t *dwin, glui32 key)
{
    static command_t cmdacceptline = { gcmd_grid_accept_line, 0 };
    static command_t cmdacceptlineterm = { gcmd_grid_accept_line, -1 };
    static command_t cmdinsert = { gcmd_grid_insert_key, -1 };
    static command_t cmdmoveleft = { gcmd_grid_move_cursor, gcmd_Left };
    static command_t cmdmoveright = { gcmd_grid_move_cursor, gcmd_Right };
    static command_t cmdmoveleftend = { gcmd_grid_move_cursor, gcmd_LeftEnd };
    static command_t cmdmoverightend = { gcmd_grid_move_cursor, gcmd_RightEnd };
    static command_t cmddelete = { gcmd_grid_delete, gcmd_Delete };
    static command_t cmddeletenext = { gcmd_grid_delete, gcmd_DeleteNext };
    static command_t cmdkillinput = { gcmd_grid_delete, gcmd_KillInput };
    static command_t cmdkillline = { gcmd_grid_delete, gcmd_KillLine };

    if (key >= 32 && key < 256 && key != 127)
        return &cmdinsert;

    switch (key) {
    case keycode_Return:
    case '\012': /* ctrl-J */
    case '\015': /* ctrl-M */
        return &cmdacceptline;
    case keycode_Left:
    case '\002': /* ctrl-B */
        return &cmdmoveleft;
    case keycode_Right:
    case '\006': /* ctrl-F */
        return &cmdmoveright;
    case keycode_Home:
    case '\001': /* ctrl-A */
        return &cmdmoveleftend;
    case keycode_End:
    case '\005': /* ctrl-E */
        return &cmdmoverightend;
    case keycode_Delete:
    case '\177': /* delete */
    case '\010': /* backspace */
        return &cmddelete;
    case '\004': /* ctrl-D */
        return &cmddeletenext;
    case '\013': /* ctrl-K */
        return &cmdkillline;
    case '\025': /* ctrl-U */
        return &cmdkillinput;
    case '\033': /* escape */
        if (dwin->intermkeys & 0x10000)
            return &cmdacceptlineterm;
        break;
#ifdef KEY_F
    case KEY_F(1):
        if (dwin->intermkeys & (1<<1))
            return &cmdacceptlineterm;
        break;
    case KEY_F(2):
        if (dwin->intermkeys & (1<<2))
            return &cmdacceptlineterm;
        break;
    case KEY_F(3):
        if (dwin->intermkeys & (1<<3))
            return &cmdacceptlineterm;
        break;
    case KEY_F(4):
        if (dwin->intermkeys & (1<<4))
            return &cmdacceptlineterm;
        break;
    case KEY_F(5):
        if (dwin->intermkeys & (1<<5))
            return &cmdacceptlineterm;
        break;
    case KEY_F(6):
        if (dwin->intermkeys & (1<<6))
            return &cmdacceptlineterm;
        break;
    case KEY_F(7):
        if (dwin->intermkeys & (1<<7))
            return &cmdacceptlineterm;
        break;
    case KEY_F(8):
        if (dwin->intermkeys & (1<<8))
            return &cmdacceptlineterm;
        break;
    case KEY_F(9):
        if (dwin->intermkeys & (1<<9))
            return &cmdacceptlineterm;
        break;
    case KEY_F(10):
        if (dwin->intermkeys & (1<<10))
            return &cmdacceptlineterm;
        break;
    case KEY_F(11):
        if (dwin->intermkeys & (1<<11))
            return &cmdacceptlineterm;
        break;
    case KEY_F(12):
        if (dwin->intermkeys & (1<<12))
            return &cmdacceptlineterm;
        break;
#endif /* KEY_F */
    }

    /* Non-Latin1 glyphs valid in this locale */
    if ( key > 256 && iswprint (glui32_to_wchar(key)) )
        return &cmdinsert;

    return NULL;
}