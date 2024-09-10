/* Prints a prompt and gets a yes or no answer - returns FALSE if ESC was
    pressed, TRUE if not. */
int getyesno(int *yesno, char *prompt)
{
    writeprompt(prompt);
    setcursor(shortcursor);
    do {
        *yesno = toupper(getkey());
        if (*yesno == ESC) {
            setcursor(nocursor);
            return(FALSE);
        }
    }
    while (strchr("YN", *yesno) == NULL);
    setcursor(nocursor);
    return(TRUE);
} /* getyesno */