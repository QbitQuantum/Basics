gboolean
GlibUtils_AttachConsole(void)
{
   typedef BOOL (WINAPI *AttachConsoleFn)(DWORD);
   gboolean ret = TRUE;
   AttachConsoleFn _AttachConsole;
   BOOL reopenStdout;
   BOOL reopenStderr;

   if (GetConsoleWindow() != NULL) {
      goto exit;
   }

   reopenStdout = !GlibUtilsIsRedirected(STD_OUTPUT_HANDLE);
   reopenStderr = !GlibUtilsIsRedirected(STD_ERROR_HANDLE);
   if (!reopenStdout && !reopenStderr) {
      goto exit;
   }

   _AttachConsole = (AttachConsoleFn) GetProcAddress(GetModuleHandleW(L"kernel32.dll"),
                                                     "AttachConsole");
   if ((_AttachConsole != NULL && _AttachConsole(ATTACH_PARENT_PROCESS)) ||
       AllocConsole()) {
      FILE *fptr;

      if (reopenStdout) {
         fptr = _wfreopen(L"CONOUT$", L"a", stdout);
         if (fptr == NULL) {
            g_warning("_wfreopen failed for stdout/CONOUT$: %d (%s)",
                      errno, strerror(errno));
            ret = FALSE;
         }
      }

      if (reopenStderr) {
         fptr = _wfreopen(L"CONOUT$", L"a", stderr);
         if (fptr == NULL) {
            g_warning("_wfreopen failed for stderr/CONOUT$: %d (%s)",
                      errno, strerror(errno));
            ret = FALSE;
         } else {
            setvbuf(fptr, NULL, _IONBF, 0);
         }
      }
   } else {
      ret = FALSE;
   }

exit:
   if (!ret) {
      g_warning("Console redirection unavailable.");
   }
   return ret;
}