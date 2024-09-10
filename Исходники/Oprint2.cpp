void Print::endprint(HWND ohwnd) {                //put the hwnd here

    EndDoc(printdlg.hDC);
    DeleteDC(memDC);
    DeleteDC(printer_mem_dc);
    DeleteDC(printdlg.hDC);
    ReleaseDC(ohwnd, hdc);
}