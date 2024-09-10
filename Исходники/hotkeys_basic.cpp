/*
 * helper function use in AddHotkeyName to calculate an accelerator string
 * In some menus, accelerators do not perform exactly the same action as
 * the hotkey that perform a similar action.
 * this is usually the case when this action uses the current mouse position
 * for instance zoom action is ran from the F1 key or the Zoom menu.
 * a zoom uses the mouse position from a hot key and not from the menu
 * In this case, the accelerator if Shift+<hotkey>
 * But for many keys, the Shift modifier is not usable, and the accelerator is Alt+<hotkey>
 */
static void AddModifierToKey( wxString& aFullKey, const wxString & aKey )
{
    if( (aKey.Length() == 1) && (aKey[0] >= 'A')  && (aKey[0] <= 'Z'))
        // We can use Shift+<key> as accelerator and <key> for hot key
        aFullKey << wxT( "\t" ) << MODIFIER_SHIFT << aKey;
    else
        // We must use Alt+<key> as accelerator and <key> for hot key
        aFullKey << wxT( "\t" ) << MODIFIER_ALT << aKey;
}