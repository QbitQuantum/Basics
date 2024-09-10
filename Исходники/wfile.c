/* _al_win_open:
 *  Open a file with open() or _wopen() depending on whether Unicode filenames
 *  are supported by this version of Windows and compiler.
 */
int _al_win_open(const char *filename, int mode, int perm)
{
   if (!_al_win_unicode_filenames) {
      return open(filename, mode, perm);
   }
   else {
      return _wopen((wchar_t*)filename, mode, perm);
   }
}