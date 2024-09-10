void remove_keybinding(Widget window, const char *keystring, const char *fstring)
{
   int function = string_to_func(fstring, NULL);
   int keywstate = string_to_key(keystring);

   if ((function < 0) || (remove_binding(window, keywstate, function) < 0)) {
      Wprintf("Key binding \'%s\' to \'%s\' does not exist in list.",
		keystring, fstring);
   }
}