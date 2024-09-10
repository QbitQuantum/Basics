static void VGA_Poll_Text(void)
{
    char *dat, *old, *p_line;
    unsigned int X, Y;
    CHAR_INFO ch[256]; /* that should suffice for the largest text width */
    COORD siz, off;
    SMALL_RECT dest;
    HANDLE con = VGA_AlphaConsole();
    BOOL linechanged = FALSE; /* video memory area differs from stored copy? */

    /* Synchronize cursor position. */
    off.X = vga_text_x;
    off.Y = vga_text_y;
    SetConsoleCursorPosition(con,off);

    dat = VGA_AlphaBuffer();
    old = vga_text_old; /* pointer to stored video mem copy */
    siz.X = vga_text_width; siz.Y = 1;
    off.X = 0; off.Y = 0;

    /* copy from virtual VGA frame buffer to console */
    for (Y=0; Y<vga_text_height; Y++) {
	linechanged = memcmp(dat, old, vga_text_width*2);
	if (linechanged)
	{
	    /*TRACE("line %d changed\n", Y);*/
	    p_line = dat;
            for (X=0; X<vga_text_width; X++) {
                ch[X].Char.AsciiChar = *p_line++;
                /* WriteConsoleOutputA doesn't like "dead" chars */
                if (ch[X].Char.AsciiChar == '\0')
                    ch[X].Char.AsciiChar = ' ';
                ch[X].Attributes = *p_line++;
            }
            dest.Top=Y; dest.Bottom=Y;
            dest.Left=0; dest.Right=vga_text_width+1;
            WriteConsoleOutputA(con, ch, siz, off, &dest);
	    memcpy(old, dat, vga_text_width*2);
	}
	/* advance to next text line */
	dat += vga_text_width*2;
	old += vga_text_width*2;
    }
}