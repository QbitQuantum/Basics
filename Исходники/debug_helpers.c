static int debug_outputlnA_impl(const char * formatString, va_list args)
{
	HRESULT hr;
	hr = StringCchVPrintfA(g_outputBuffer, OUTPUT_BUFFER_LEN, formatString, args);
	if (SUCCEEDED(hr) || hr == STRSAFE_E_INSUFFICIENT_BUFFER)
    {
		OutputDebugStringA(g_outputBuffer);
    }
    va_end(args);
	return SUCCEEDED(hr);
}