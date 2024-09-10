/*
 * @implemented
 */
void __wgetmainargs(int* argc, wchar_t*** wargv, wchar_t*** wenv,
                    int expand_wildcards, int* new_mode)
{
   int i, afterlastspace, ignorespace, doexpand;
   size_t len;
   wchar_t* wNewCmdln;

   /* missing threading init */

   i = 0;
   afterlastspace = 0;
   ignorespace = 0;
   doexpand = expand_wildcards;

   if (__wargv && __winitenv)
   {
      *wargv = __wargv;
      *wenv = __winitenv;
      *argc = __argc;
      return;
   }

   __argc = 0;

   len = wcslen(_wcmdln);

   /* Allocate a temporary buffer to be used instead of the original _wcmdln parameter. */
   wNewCmdln = wcsndup(_wcmdln, len);

   while (wNewCmdln[i])
   {
      if (wNewCmdln[i] == L'"')
      {
         if(ignorespace)
         {
            ignorespace = 0;
         }
         else
         {
            ignorespace = 1;
            doexpand = 0;
         }
         memmove(wNewCmdln + i, wNewCmdln + i + 1, (len - i) * sizeof(wchar_t));
         len--;
         continue;
      }

      if (wNewCmdln[i] == L' ' && !ignorespace)
      {
         wexpand(wcsndup(wNewCmdln + afterlastspace, i - afterlastspace), doexpand);
         i++;
         while (wNewCmdln[i] == L' ')
            i++;
         afterlastspace=i;
         doexpand = expand_wildcards;
      }
      else
      {
         i++;
      }
   }

   if (wNewCmdln[afterlastspace] != 0)
   {
      wexpand(wcsndup(wNewCmdln + afterlastspace, i - afterlastspace), doexpand);
   }

   /* Free the temporary buffer. */
   free(wNewCmdln);

   HeapValidate(GetProcessHeap(), 0, NULL);

   *argc = __argc;
   if (__wargv == NULL)
   {
       __wargv = (wchar_t**)malloc(sizeof(wchar_t*));
       __wargv[0] = 0;
   }
   *wargv = __wargv;
   *wenv = __winitenv;
   _wpgmptr = _wcsdup(__wargv[0]);

   // if (new_mode) _set_new_mode(*new_mode);
}