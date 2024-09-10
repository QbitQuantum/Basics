static gboolean
gimp_unique_win32_open (const gchar **filenames,
			gboolean      as_new)
{
#ifndef GIMP_CONSOLE_COMPILATION

/*  for the proxy window names  */
#include "gui/gui-unique.h"

  HWND  window_handle = FindWindowW (GIMP_UNIQUE_WIN32_WINDOW_CLASS,
				     GIMP_UNIQUE_WIN32_WINDOW_NAME);

  if (window_handle)
    {
      COPYDATASTRUCT  copydata = { 0, };

      if (filenames)
        {
          gchar  *cwd   = g_get_current_dir ();
          gint    i;

          for (i = 0; filenames[i]; i++)
            {
              GFile *file;
              file = g_file_new_for_commandline_arg_and_cwd (filenames[i], cwd);

              if (file)
                {
                  gchar *uri = g_file_get_uri (file);

                  copydata.lpData = uri;
                  copydata.cbData = strlen (uri) + 1;  /* size in bytes   */
                  copydata.dwData = (long) as_new;

                  SendMessage (window_handle,
                               WM_COPYDATA, (WPARAM) window_handle, (LPARAM) &copydata);

                  g_free (uri);
                  g_object_unref (file);
                }
              else
                {
                  g_printerr ("conversion to uri failed for '%s'\n",
                              filenames[i]);
                }
            }

          g_free (cwd);
        }
      else
        {
          SendMessage (window_handle,
                       WM_COPYDATA, (WPARAM) window_handle, (LPARAM) &copydata);
        }

      return TRUE;
    }

#endif

  return FALSE;
}