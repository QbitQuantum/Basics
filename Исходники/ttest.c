static void create_dialog()
{
    setcursor(ArrowCursor);  /* not `busy' cursor */
    win = newwindow("t-test entry", rect(0, 0, 200, 200),
                    Titlebar | Centered | Modal);
    setbackground(win, dialog_bg());
    setkeydown(win, hit_key);
    bApply = newbutton("Apply", rect(20, 160, 50, 25), apply);
    bCancel = newbutton("Cancel", rect(120, 160, 50, 25), NULL);
    l_var1 = newlabel("x", rect(10, 10, 30, 20), AlignLeft);
    var1 = newfield("", rect(40, 10, 130, 20));
    l_var2 = newlabel("y", rect(10, 40, 30, 20), AlignLeft);
    var2 = newfield("", rect(40, 40, 130, 20));
    paired = newcheckbox("paired", rect(10, 70, 80, 20), NULL);
    varequal = newcheckbox("equal var", rect(110, 70, 80, 20), NULL);
    alt = newdroplist(alts , rect(30, 90, 120, 20), NULL);
    setlistitem(alt, 0);
    l_lvl = newlabel("confidence level", rect(20, 120, 90, 20), AlignLeft);
    lvl = newfield("0.95", rect(120, 120, 40, 20));
}