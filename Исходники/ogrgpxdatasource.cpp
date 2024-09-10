void OGRGPXDataSource::PrintLine(const char *fmt, ...)
{
    CPLString osWork;
    va_list args;

    va_start( args, fmt );
    osWork.vPrintf( fmt, args );
    va_end( args );

    VSIFPrintfL(fpOutput, "%s%s", osWork.c_str(), pszEOL);
}