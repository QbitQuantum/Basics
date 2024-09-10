/**
 * If we can determine the WGL extension support from the current
 * context, then return that, otherwise give the answer that will just
 * send us on to get_proc_address().
 */
bool
epoxy_conservative_has_wgl_extension(const char *ext)
{
    HDC hdc = wglGetCurrentDC();

    if (!hdc)
        return true;

    return epoxy_has_wgl_extension(hdc, ext);
}