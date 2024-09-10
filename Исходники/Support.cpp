void FakeClientCommand (edict_t *fakeClient, const char *format, ...)
{
   // the purpose of this function is to provide fakeclients (bots) with the same client
   // command-scripting advantages (putting multiple commands in one line between semicolons)
   // as real players. It is an improved version of botman's FakeClientCommand, in which you
   // supply directly the whole string as if you were typing it in the bot's "console". It
   // is supposed to work exactly like the pfnClientCommand (server-sided client command).

   va_list ap;
   static char command[256];
   int start, stop, i, index, stringIndex = 0;

   if (FNullEnt (fakeClient))
      return; // reliability check

   // concatenate all the arguments in one string
   va_start (ap, format);
   _vsnprintf (command, sizeof (command), format, ap);
   va_end (ap);

   if (IsNullString (command))
      return; // if nothing in the command buffer, return

   g_isFakeCommand = true; // set the "fakeclient command" flag
   int length = strlen (command); // get the total length of the command string

   // process all individual commands (separated by a semicolon) one each a time
   while (stringIndex < length)
   {
      start = stringIndex; // save field start position (first character)

      while (stringIndex < length && command[stringIndex] != ';')
         stringIndex++; // reach end of field

      if (command[stringIndex - 1] == '\n')
         stop = stringIndex - 2; // discard any trailing '\n' if needed
      else
         stop = stringIndex - 1; // save field stop position (last character before semicolon or end)

      for (i = start; i <= stop; i++)
         g_fakeArgv[i - start] = command[i]; // store the field value in the g_fakeArgv global string

      g_fakeArgv[i - start] = 0; // terminate the string
      stringIndex++; // move the overall string index one step further to bypass the semicolon

      index = 0;
      g_fakeArgc = 0; // let's now parse that command and count the different arguments

      // count the number of arguments
      while (index < i - start)
      {
         while (index < i - start && g_fakeArgv[index] == ' ')
            index++; // ignore spaces

         // is this field a group of words between quotes or a single word ?
         if (g_fakeArgv[index] == '"')
         {
            index++; // move one step further to bypass the quote

            while (index < i - start && g_fakeArgv[index] != '"')
               index++; // reach end of field

            index++; // move one step further to bypass the quote
         }
         else
            while (index < i - start && g_fakeArgv[index] != ' ')
               index++; // this is a single word, so reach the end of field

         g_fakeArgc++; // we have processed one argument more
      }

      // tell now the MOD DLL to execute this ClientCommand...
      MDLL_ClientCommand (fakeClient);
   }

   g_fakeArgv[0] = 0; // when it's done, reset the g_fakeArgv field
   g_isFakeCommand = false; // reset the "fakeclient command" flag
   g_fakeArgc = 0; // and the argument count
}