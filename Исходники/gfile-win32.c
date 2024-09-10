int mkstemp (char *tmp_template)
{
    int fd;
    gunichar2* utf16_template;

    utf16_template  = u8to16 (tmp_template);

    fd = -1;
    utf16_template = _wmktemp( utf16_template);
    if (utf16_template && *utf16_template) {
        /* FIXME: _O_TEMPORARY causes file to disappear on close causing a test to fail */
        fd = _wopen( utf16_template, _O_BINARY | _O_CREAT /*| _O_TEMPORARY*/ | _O_RDWR | _O_EXCL, _S_IREAD | _S_IWRITE);
    }

    /* FIXME: this will crash if utf16_template == NULL */
    sprintf (tmp_template + strlen (tmp_template) - 6, "%S", utf16_template + wcslen (utf16_template) - 6);

    g_free (utf16_template);
    return fd;
}