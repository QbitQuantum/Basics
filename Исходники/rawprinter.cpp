void RawPrinter::close()
{
    if (opened) {
        ClosePrinter(hPrinter);
        opened = false;
    }
}