static FILE *JsiFdOpenForWrite(fdtype fd)
{
    return _fdopen(_open_osfhandle((int)fd, _O_TEXT), "w");
}