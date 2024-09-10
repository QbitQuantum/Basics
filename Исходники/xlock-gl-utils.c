/* Callback in xscreensaver_function_table, via xlockmore.c.
 */
Visual *
xlockmore_pick_gl_visual (Screen *screen)
{
    /* pick the "best" visual by interrogating the GL library instead of
       by asking Xlib.  GL knows better.
     */
    Visual *v = 0;
    Display *dpy = DisplayOfScreen (screen);
    char *string = get_string_resource (dpy, "visualID", "VisualID");
    char *s;

    if (string)
        for (s = string; *s; s++)
            if (isupper (*s)) *s = _tolower (*s);

    if (!string || !*string ||
            !strcmp (string, "gl") ||
            !strcmp (string, "best") ||
            !strcmp (string, "color") ||
            !strcmp (string, "default"))
        v = get_gl_visual (screen);		/* from ../utils/visual-gl.c */

    if (string)
        free (string);

    return v;
}