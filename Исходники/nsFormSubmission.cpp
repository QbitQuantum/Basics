nsresult
nsFSMultipartFormData::AddNameBlobOrNullPair(const nsAString& aName,
                                             Blob* aBlob)
{
  // Encode the control name
  nsAutoCString nameStr;
  nsresult rv = EncodeVal(aName, nameStr, true);
  NS_ENSURE_SUCCESS(rv, rv);

  nsAutoCString filename;
  nsAutoCString contentType;
  nsCOMPtr<nsIInputStream> fileStream;

  if (aBlob) {
    nsAutoString filename16;
    RetrieveFileName(aBlob, filename16);

    ErrorResult error;
    nsAutoString filepath16;
    RefPtr<File> file = aBlob->ToFile();
    if (file) {
      file->GetPath(filepath16, error);
      if (NS_WARN_IF(error.Failed())) {
        return error.StealNSResult();
      }
    }

    if (!filepath16.IsEmpty()) {
      // File.path includes trailing "/"
      filename16 = filepath16 + filename16;
    }

    rv = EncodeVal(filename16, filename, true);
    NS_ENSURE_SUCCESS(rv, rv);

    // Get content type
    nsAutoString contentType16;
    aBlob->GetType(contentType16);
    if (contentType16.IsEmpty()) {
      contentType16.AssignLiteral("application/octet-stream");
    }

    contentType.Adopt(nsLinebreakConverter::
                      ConvertLineBreaks(NS_ConvertUTF16toUTF8(contentType16).get(),
                                        nsLinebreakConverter::eLinebreakAny,
                                        nsLinebreakConverter::eLinebreakSpace));

    // Get input stream
    aBlob->GetInternalStream(getter_AddRefs(fileStream), error);
    if (NS_WARN_IF(error.Failed())) {
      return error.StealNSResult();
    }

    if (fileStream) {
      // Create buffered stream (for efficiency)
      nsCOMPtr<nsIInputStream> bufferedStream;
      rv = NS_NewBufferedInputStream(getter_AddRefs(bufferedStream),
                                     fileStream, 8192);
      NS_ENSURE_SUCCESS(rv, rv);

      fileStream = bufferedStream;
    }
  } else {
    contentType.AssignLiteral("application/octet-stream");
  }

  //
  // Make MIME block for name/value pair
  //
  // more appropriate than always using binary?
  mPostDataChunk += NS_LITERAL_CSTRING("--") + mBoundary
                 + NS_LITERAL_CSTRING(CRLF);
  // XXX: name/filename parameter should be encoded per RFC 2231
  // RFC 2388 specifies that RFC 2047 be used, but I think it's not
  // consistent with the MIME standard.
  mPostDataChunk +=
         NS_LITERAL_CSTRING("Content-Disposition: form-data; name=\"")
       + nameStr + NS_LITERAL_CSTRING("\"; filename=\"")
       + filename + NS_LITERAL_CSTRING("\"" CRLF)
       + NS_LITERAL_CSTRING("Content-Type: ")
       + contentType + NS_LITERAL_CSTRING(CRLF CRLF);

  // We should not try to append an invalid stream. That will happen for example
  // if we try to update a file that actually do not exist.
  if (fileStream) {
    ErrorResult error;
    uint64_t size = aBlob->GetSize(error);
    if (error.Failed()) {
      error.SuppressException();
    } else {
      // We need to dump the data up to this point into the POST data stream
      // here, since we're about to add the file input stream
      AddPostDataStream();

      mPostDataStream->AppendStream(fileStream);
      mTotalLength += size;
    }
  }

  // CRLF after file
  mPostDataChunk.AppendLiteral(CRLF);

  return NS_OK;
}