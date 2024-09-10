void
_pci_bdfprintf (int bus, int device, int function, const char *fmt, ...)
{
    va_list arg;

    print_bdf (bus, device, function);
    va_start(arg, fmt);
    VPRINTF (fmt, arg);
    va_end(arg);
}