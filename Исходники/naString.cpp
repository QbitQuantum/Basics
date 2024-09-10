bool naStringFormatV( std::wstring& rstrOutput, const wchar_t* format, va_list ap)
{
    wchar_t wszLocalBuffer[256];
    va_list vaClone;

    va_copy(vaClone, ap);
    int nOutputSize = _vsnwprintf(wszLocalBuffer, sizeof(wszLocalBuffer)/sizeof(wszLocalBuffer[0]), format, vaClone);
    va_end(vaClone);
    if( nOutputSize < 0 )
        return false;
    if( nOutputSize < (sizeof(wszLocalBuffer)/sizeof(wszLocalBuffer[0]))) {
        rstrOutput.assign( wszLocalBuffer, nOutputSize );
        return true;
    }

    wchar_t* szDynamicBuffer = new wchar_t[nOutputSize+1];
    va_copy(vaClone, ap);
    nOutputSize = _vsnwprintf(szDynamicBuffer, nOutputSize+1, format, vaClone);
    va_end(vaClone);
    if( nOutputSize < 0 ) {
        delete[] szDynamicBuffer;
        return false;
    }
    rstrOutput.append( szDynamicBuffer, nOutputSize );
    delete[] szDynamicBuffer;
    return true;
}