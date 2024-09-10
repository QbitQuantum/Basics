gboolean free_key(GdkDisplay* gdisplay,
		  GdkWindow* groot,
		  HotkeyEntry* key)
{
    ATOM atom;
    gboolean retval;

    if (!key->code || !key->mod)
        return FALSE;
  
    if (!(atom = find_hotkey_atom(key)))
	return FALSE;
    
    retval = UnregisterHotKey(get_dummy_win(), atom);
    GlobalDeleteAtom(atom);

    return retval;
}