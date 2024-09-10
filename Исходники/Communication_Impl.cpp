//-----------------------------------------------------------------------------
/// Generates an HTTP header according to the options stored in the Response
//-----------------------------------------------------------------------------
void GenerateHeader(Response& rResponse, char* pOut, DWORD dwBufferSize)
{
    strcpy_s(pOut, dwBufferSize, "HTTP/1.0 200 OK\r\n");

    if (rResponse.m_bSendNoCache == true)
    {
        strncat_s(pOut, dwBufferSize, "pragma: no-store, no-cache\r\n"
                  "cache-control: no-cache, no-store, must-revalidate, max-age = 0\r\n"
                  "expires: 0\r\n",
                  COMM_BUFFER_SIZE);
    }

    if (rResponse.m_bStreamingEnabled == true)
    {
        strncat_s(pOut, dwBufferSize, "Content-Type: multipart/x-mixed-replace; boundary=BoundaryString\r\n\r\n", COMM_BUFFER_SIZE);
    }
}