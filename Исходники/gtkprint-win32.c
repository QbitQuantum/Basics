/*
 * Used to get printer device information from a printer name.  This
 * can fail if the user has no right to read printer properties, so
 * this function can return NULL.
 */
GtkPrintWin32Devnames *
gtk_print_win32_devnames_from_printer_name (const char *printer_name)
{
  HANDLE hprinter;
  gunichar2* win32_printer_name;
  GtkPrintWin32Devnames *devnames;

  win32_printer_name = g_utf8_to_utf16 (printer_name, -1, NULL, NULL, NULL);
  if (OpenPrinterW (win32_printer_name, &hprinter, NULL))
    {
      DWORD needed;
      PRINTER_INFO_2W* printer_info;

      GetPrinterW (hprinter, 2, NULL, 0, &needed);
      printer_info = (PRINTER_INFO_2W* )g_malloc ((gsize) needed);
      GetPrinterW (hprinter, 2, (LPBYTE) printer_info, needed, &needed);
      devnames = g_new (GtkPrintWin32Devnames, 1);
      devnames->driver = g_utf16_to_utf8 (printer_info->pDriverName, -1, NULL, NULL, NULL);
      devnames->device = g_strdup (printer_name);
      devnames->output = g_utf16_to_utf8 (printer_info->pPortName, -1, NULL, NULL, NULL);
      devnames->flags  = 0;
      ClosePrinter (hprinter);
      g_free (printer_info);
    }
  else
    {
      /* Could not open printer */
      devnames = NULL;
    }
  g_free (win32_printer_name);

  return devnames;
}