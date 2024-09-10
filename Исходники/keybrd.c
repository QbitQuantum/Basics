static void
kbinitmap(VOID)
{
    (void)Memset((void*)&keymap[0],(int)KEYBOARD_UNKNOWN,sizeof(keymap));

    keymap[(unsigned)'b']	= KEYBOARD_PGUP;
    keymap[(unsigned)'B']	= KEYBOARD_PGUP;
    keymap[(unsigned)META('V')]	= KEYBOARD_PGUP; /* Emacs scroll-down */

    keymap[(unsigned)'\r']	= KEYBOARD_DOWN; /* the less and more pagers bind */
    keymap[(unsigned)'\n']	= KEYBOARD_DOWN; /* these keys to KEYBOARD_DOWN */
    keymap[(unsigned)'d']	= KEYBOARD_DOWN;
    keymap[(unsigned)'D']	= KEYBOARD_DOWN;
    keymap[(unsigned)CTL('N')]	= KEYBOARD_DOWN; /* Emacs next-line*/

    keymap[(unsigned)'e']	= KEYBOARD_END;
    keymap[(unsigned)'E']	= KEYBOARD_END;
    keymap[(unsigned)META('>')]	= KEYBOARD_END; /* Emacs end-of-buffer */
    keymap[(unsigned)'>']	= KEYBOARD_END;

    keymap[(unsigned)'f']	= KEYBOARD_PGDN;
    keymap[(unsigned)'F']	= KEYBOARD_PGDN;
    keymap[(unsigned)' ']	= KEYBOARD_PGDN;
    keymap[(unsigned)CTL('V')]	= KEYBOARD_PGDN; /* Emacs scroll-up */

    keymap[(unsigned)'h']	= KEYBOARD_HELP;
    keymap[(unsigned)'H']	= KEYBOARD_HELP;
    keymap[(unsigned)'?']	= KEYBOARD_HELP;
    keymap[(unsigned)CH_BACKSPACE] = KEYBOARD_HELP; /* Emacs help */

    keymap[(unsigned)CH_ESCAPE]	= KEYBOARD_QUIT; /* ESCape gets out */
    keymap[(unsigned)'q']	= KEYBOARD_QUIT;
    keymap[(unsigned)'Q']	= KEYBOARD_QUIT;

    keymap[(unsigned)'.']	= KEYBOARD_AGAIN;
    keymap[(unsigned)'r']	= KEYBOARD_AGAIN;
    keymap[(unsigned)'R']	= KEYBOARD_AGAIN;
    keymap[(unsigned)CTL('L')]	= KEYBOARD_AGAIN; /* Emacs recenter */

    keymap[(unsigned)'t']	= KEYBOARD_HOME;
    keymap[(unsigned)'T']	= KEYBOARD_HOME;
    keymap[(unsigned)META('<')]	= KEYBOARD_HOME; /* Emacs beginning-of-buffer */
    keymap[(unsigned)'<']	= KEYBOARD_HOME;

    keymap[(unsigned)CTL('R')]	= KEYBOARD_SEARCH_BACKWARD; /* Emacs */
    keymap[(unsigned)'\\']	= KEYBOARD_SEARCH_BACKWARD;

    keymap[(unsigned)CTL('S')]	= KEYBOARD_SEARCH_FORWARD; /* Emacs */
    keymap[(unsigned)'/']	= KEYBOARD_SEARCH_FORWARD;

    keymap[(unsigned)'u']	= KEYBOARD_UP;
    keymap[(unsigned)'U']	= KEYBOARD_UP;
    keymap[(unsigned)CTL('P')]	= KEYBOARD_UP; 	/* Emacs previous-line */

    keymap[(unsigned)'[']	= KEYBOARD_UP_PARAGRAPH;
    keymap[(unsigned)']']	= KEYBOARD_DOWN_PARAGRAPH;

    keymap[(unsigned)'{']	= KEYBOARD_UP_PARAGRAPH;
    keymap[(unsigned)'}']	= KEYBOARD_DOWN_PARAGRAPH;
}