int string_to_key(const char *keystring)
{
   int ct, keywstate = 0;
   const char *kptr = keystring;

   while(1) {
      if (*kptr == '\0') return -1;
      if (!strncmp(kptr, "XK_", 3))
	 kptr += 3;
      else if (!strncmp(kptr, "Shift_", 6)) {
	 keywstate |= SHIFT;
	 kptr += 6;
      }
      else if (!strncmp(kptr, "Capslock_", 9)) {
	 keywstate |= CAPSLOCK;
	 kptr += 9;
      }
      else if (!strncmp(kptr, "Control_", 8)) {
	 keywstate |= CTRL;
	 kptr += 8;
      }
      else if (!strncmp(kptr, "Alt_", 4)) {
	 keywstate |= ALT;
	 kptr += 4;
      }
      else if (!strncmp(kptr, "Meta_", 5)) {
	 keywstate |= ALT;
	 kptr += 5;
      }
      else if (!strncmp(kptr, "Hold_", 5)) {
	 keywstate |= HOLD;
	 kptr += 5;
      }
      else if (*kptr == '^') {
	 kptr++;
	 ct = (int)tolower(*kptr);
	 keywstate |= CTRL | ct;
	 break;
      }
      else if (*(kptr + 1) == '\0') {
	 if ((*kptr) < 32)
	    keywstate |= CTRL | (int)('A' + (*kptr) - 1);
	 else
	    keywstate |= (int)(*kptr);
	 break;
      }
      else {
         if (!strncmp(kptr, "Button", 6)) {
	    switch (*(kptr + 6)) {
	       case '1': keywstate = (Button1Mask << 16); break;
	       case '2': keywstate = (Button2Mask << 16); break;
	       case '3': keywstate = (Button3Mask << 16); break;
	       case '4': keywstate = (Button4Mask << 16); break;
	       case '5': keywstate = (Button5Mask << 16); break;
	    }
         }
	 else {
	    /* When any modifier keys are used, presence of SHIFT */
	    /* requires that the corresponding key be uppercase,  */
	    /* and lack of SHIFT requires lowercase.  Enforce it  */
	    /* here so that it is not necessary for the user to	  */
	    /* do so.						  */
	    if (*(kptr + 1) == '\0') {
	       if (keywstate & SHIFT)
	          ct = (int)toupper(*kptr);
	       else
	          ct = (int)tolower(*kptr);
	       keywstate |= ct;
	    }
	    else
	       keywstate |= XStringToKeysym(kptr);
	 }
	 break;
      }
   }
   return keywstate;
}