// Returns the Secure Base URL to MSXML.
HRESULT CSiteImpl::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
    return CreateURLMoniker(NULL, _secureBaseURL.c_str(), ppmk);
}