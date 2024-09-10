/**
 * Calculates the checksums from the given stream.
 *
 * @param  in         Input stream from which the data will be extracted to
 *                    compute the checksum. The data are extracted until the end
 *                    of the stream is reached.
 * @param  checksums  Array of checksums to calculate.
 * @param  sumValues  The calculated values of the checksums from the input
 *                    stream. The array is erased first before adding results.
 *                    On success <CODE>ArrayChecksum.GetCount() == sumValues.GetCount()</CODE>,
 *                    on failure, <CODE>sumValues</CODE> should be empty.
 * @return <UL>
 *           <LI><CODE>Ok</CODE> if the checksum has been successfully calculated.</Li>
 *           <LI><CODE>ReadError</CODE> if a read error has occured.</LI>
 *           <LI><CODE>Canceled</CODE> if the user has canceled the calculation.</LI>
 *         </UL>
 */
ChecksumCalculator::State ChecksumCalculator::calculate(wxInputStream& in,
                                                 const ArrayChecksum& checksums,
                                                       wxArrayString& sumValues)
{
  // Check if the input stream is valid.
  if (!in.IsOk())
    return ReadError;
  
  // Check if at least a checksum instance is OK.
  bool aInstanceOK = false;
  size_t i = 0;
  size_t s = checksums.GetCount();
  while (!aInstanceOK && i < s)
    if (checksums[i] != NULL)
      aInstanceOK = true;
    else
      i++;
  if (!aInstanceOK)
    return ReadError;
  
  // Initializes the buffer.
  const size_t bufSize = getBufferSize();
  wxByte* buff = new wxByte[bufSize];

  // Calculating the checksum.
  ChecksumProgress* p = getChecksumProgress();
  bool canceled = false;
  size_t read;
  wxStreamError lastError = wxSTREAM_NO_ERROR;
  s = checksums.GetCount();
  for (i = 0; i < s; i++)
    if (checksums[i] != NULL)
      checksums[i]->reset();
  while (!canceled && !in.Eof() && lastError == wxSTREAM_NO_ERROR)
  {
    in.Read(buff, bufSize);
    read = in.LastRead();
    if (read > 0 && read <= bufSize)
    {
      for (i = 0; i < s; i++)
        if (checksums[i] != NULL)
          checksums[i]->update(buff, read);
      if (p != NULL)
        p->update(read, canceled);
    }
    lastError = in.GetLastError();
  }

  // Cleans-up the memory
  delete[] buff;
  
  if (canceled)
    return CanceledByUser;
  
  if (lastError != wxSTREAM_NO_ERROR && lastError != wxSTREAM_EOF)
    return ReadError;
    
  sumValues.Empty();
  for (i = 0; i < s; i++)
    if (checksums[i] != NULL)
      sumValues.Add(checksums[i]->getValue());
    else
      sumValues.Add(wxEmptyString);

  return Ok;
}