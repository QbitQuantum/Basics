nsresult
nsWebSocket::ConvertTextToUTF8(const nsString& aMessage, nsCString& buf)
{
  NS_ABORT_IF_FALSE(NS_IsMainThread(), "Not running on main thread");
  nsresult rv;

  nsCOMPtr<nsICharsetConverterManager> ccm =
    do_GetService(NS_CHARSETCONVERTERMANAGER_CONTRACTID, &rv);
  SUCCESS_OR_FAIL_WEBSOCKET(rv, rv);

  nsCOMPtr<nsIUnicodeEncoder> converter;
  rv = ccm->GetUnicodeEncoder("UTF-8", getter_AddRefs(converter));
  SUCCESS_OR_FAIL_WEBSOCKET(rv, rv);

  rv = converter->SetOutputErrorBehavior(nsIUnicodeEncoder::kOnError_Replace,
                                         nsnull, UTF_8_REPLACEMENT_CHAR);
  SUCCESS_OR_FAIL_WEBSOCKET(rv, rv);

  PRInt32 inLen = aMessage.Length();
  PRInt32 maxLen;
  rv = converter->GetMaxLength(aMessage.BeginReading(), inLen, &maxLen);
  SUCCESS_OR_FAIL_WEBSOCKET(rv, rv);

  buf.SetLength(maxLen);
  TRUE_OR_FAIL_WEBSOCKET(buf.Length() == static_cast<PRUint32>(maxLen),
                         NS_ERROR_OUT_OF_MEMORY);

  char* start = buf.BeginWriting();

  PRInt32 outLen = maxLen;
  rv = converter->Convert(aMessage.BeginReading(), &inLen, start, &outLen);
  if (NS_SUCCEEDED(rv)) {
    PRInt32 outLen2 = maxLen - outLen;
    rv = converter->Finish(start + outLen, &outLen2);
    outLen += outLen2;
  }
  if (NS_FAILED(rv) || rv == NS_ERROR_UENC_NOMAPPING) {
    // Yes, NS_ERROR_UENC_NOMAPPING is a success code
    return NS_ERROR_DOM_SYNTAX_ERR;
  }

  buf.SetLength(outLen);
  TRUE_OR_FAIL_WEBSOCKET(buf.Length() == static_cast<PRUint32>(outLen),
                         NS_ERROR_UNEXPECTED);

  return NS_OK;
}