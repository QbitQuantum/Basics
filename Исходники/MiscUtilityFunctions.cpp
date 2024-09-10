void Win32AllocateStdioConsole(const char * optArg)
{
   const String optOutFile = optArg;

   const char * conInStr  = optOutFile.HasChars() ? NULL         : "conin$";
   const char * conOutStr = optOutFile.HasChars() ? optOutFile() : "conout$";
   if (optOutFile.IsEmpty()) AllocConsole();  // no sense creating a DOS window if we're only outputting to a file anyway

   // Hopefully-temporary work-around for Windows not wanting to send stdout and stderr to the same file
   String conErrHolder;  // don't move this!  It needs to stay here
   const char * conErrStr = NULL;
   if (optOutFile.HasChars())
   {
      const int lastDotIdx = optOutFile.LastIndexOf('.');

      if (lastDotIdx > 0)
         conErrHolder = optOutFile.Substring(0, lastDotIdx) + "_stderr" + optOutFile.Substring(lastDotIdx);
      else
         conErrHolder = optOutFile + "_stderr.txt";

      conErrStr = conErrHolder();
   }
   else conErrStr = conOutStr;  // for the output-to-console-window case, where redirecting both stdout and stderr DOES work

# if __STDC_WANT_SECURE_LIB__
   FILE * junk;
   if (conInStr)  (void) freopen_s(&junk, conInStr,  "r", stdin);
   if (conOutStr) (void) freopen_s(&junk, conOutStr, "w", stdout);
   if (conErrStr) (void) freopen_s(&junk, conErrStr, "w", stderr);
# else
   if (conInStr)  (void) freopen(conInStr,  "r", stdin);
   if (conOutStr) (void) freopen(conOutStr, "w", stdout);
   if (conErrStr) (void) freopen(conErrStr, "w", stderr);
# endif
}