//
/// WM_PAINT handler of RichEdit PagePreview window. Displays a preview of the page
/// if the printout can handle it. Otherwise, simply fills the window with a white
/// background.
//
void
TRichEditPagePreview::Paint(TDC& dc, bool, TRect& /*clip*/)
{
    TRect client;
    GetClientRect(client);

    TPreviewDCBase pdc(dc, PrintDC);
    Printout.SetPrintParams(&pdc, PrintExtent);

    if (Printout.HasPage(PageNum)) {
        Printout.BeginPrinting();
        Printout.BeginDocument(PageNum, PageNum, pfBoth);
        Printout.PrintPage(PageNum, client, pfBoth);
        Printout.EndDocument();
        Printout.EndPrinting();
    }
    else
        dc.PatBlt(client, WHITENESS);
}