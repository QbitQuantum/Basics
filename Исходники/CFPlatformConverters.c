CF_INLINE bool __CFIsPlatformConverterAvailable(int encoding) {

#if DEPLOYMENT_TARGET_WINDOWS
    return (IsValidCodePage(CFStringConvertEncodingToWindowsCodepage(encoding)) ? true : false);
#else
    return false;
#endif
}