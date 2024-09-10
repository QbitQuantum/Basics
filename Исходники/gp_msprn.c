void mswin_printer_thread(void *arg)
{
    int fd = (int)arg;
    char pname[gp_file_name_sizeof];
    char data[4096];
    HANDLE hprinter = INVALID_HANDLE_VALUE;
    int count;
    DWORD written;
    DOC_INFO_1 di;

    /* Read from pipe and write to Windows printer.
     * First gp_file_name_sizeof bytes are name of the printer.
     */
    if (read(fd, pname, sizeof(pname)) != sizeof(pname)) {
	/* Didn't get the printer name */
	close(fd);
	return;
    }

    while ( (count = read(fd, data, sizeof(data))) > 0 ) {
	if (hprinter == INVALID_HANDLE_VALUE) {
	    if (!OpenPrinter(pname, &hprinter, NULL)) {
		close(fd);
		return;
	    }
	    di.pDocName = (LPTSTR)gs_product;
	    di.pOutputFile = NULL;
	    di.pDatatype = "RAW";
	    if (!StartDocPrinter(hprinter, 1, (LPBYTE) & di)) {
		AbortPrinter(hprinter);
		close(fd);
		return;
	    }
	}
	if (!StartPagePrinter(hprinter)) {
		AbortPrinter(hprinter);
		close(fd);
		return;
	}
	if (!WritePrinter(hprinter, (LPVOID) data, count, &written)) {
	    AbortPrinter(hprinter);
	    close(fd);
	    return;
	}
    }
    if (hprinter != INVALID_HANDLE_VALUE) {
	if (count == 0) {
	    /* EOF */
	    EndPagePrinter(hprinter);
	    EndDocPrinter(hprinter);
	    ClosePrinter(hprinter);
	}
	else {
	    /* Error */
	    AbortPrinter(hprinter);
	}
    }
    close(fd);
}