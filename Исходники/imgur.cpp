bool uploadToImgur(Image* image, String& response)
{
  MemWriteFile memRaw;
  image->writePNG(&memRaw);

  bool success = false;
  response = "Failed to connect";
  HINTERNET hSession = WinHttpOpen(L"MuleView", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, NULL, NULL, 0);
  if (hSession)
  {
    HINTERNET hConnect = WinHttpConnect(hSession, L"api.imgur.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (hConnect)
    {
      HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/3/image", L"HTTP/1.1",
        WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
      if (hRequest)
      {
        wchar_t* headers = L"Authorization: Client-ID b7668fe01959177\r\n"
                           L"Content-Type: image/png\r\n";
        BOOL result = WinHttpSendRequest(hRequest, headers, -1, memRaw.buffer(), memRaw.size(), memRaw.size(), NULL);
        if (result)
          result = WinHttpReceiveResponse(hRequest, NULL);
        DWORD avail;
        if (result)
          result = WinHttpQueryDataAvailable(hRequest, &avail);
        if (result)
        {
          char* ptr = new char[avail + 1];
          WinHttpReadData(hRequest, ptr, avail, &avail);
          ptr[avail] = 0;
          LocalPtr<json::Value> value = json::Value::parse(File::memfile(ptr, avail, false));
          json::Value* sub = (value && value->type() == json::Value::tObject ? value->get("data") : NULL);
          json::Value* sub2 = (sub && sub->type() == json::Value::tObject ? sub->get("id") : NULL);
          if (sub2 && sub2->type() == json::Value::tString)
          {
            success = true;
            response = sub2->getString();
          }
          else
          {
            sub2 = (sub && sub->type() == json::Value::tObject ? sub->get("error") : NULL);
            if (sub2 && sub2->type() == json::Value::tString)
              response = sub2->getString();
          }
          delete[] ptr;
        }
        WinHttpCloseHandle(hRequest);
      }
      WinHttpCloseHandle(hConnect);
    }
    WinHttpCloseHandle(hSession);
  }
  return success;
}