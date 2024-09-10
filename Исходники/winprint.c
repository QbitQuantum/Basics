void
printer_start_job(char *printer_name)
{
  if (OpenPrinter(printer_name, &printer, 0)) {
    if (StartDocPrinter(printer, 1, (LPBYTE)&doc_info)) {
      if (StartPagePrinter(printer))
        return;
      EndDocPrinter(printer);
    }
    ClosePrinter(printer);
    printer = 0;
  }
}