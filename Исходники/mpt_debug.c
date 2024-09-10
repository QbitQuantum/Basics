void
mpt_prt(struct mpt_softc *mpt, const char *fmt, ...)
{
    __va_list ap;

    kprintf("%s: ", device_get_nameunit(mpt->dev));
    __va_start(ap, fmt);
    kvprintf(fmt, ap);
    __va_end(ap);
}