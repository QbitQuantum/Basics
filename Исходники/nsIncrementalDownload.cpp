// Reads the current file size and validates it.
nsresult
nsIncrementalDownload::ReadCurrentSize()
{
  int64_t size;
  nsresult rv = mDest->GetFileSize((int64_t *) &size);
  if (rv == NS_ERROR_FILE_NOT_FOUND ||
      rv == NS_ERROR_FILE_TARGET_DOES_NOT_EXIST) {
    mCurrentSize = 0;
    return NS_OK;
  }
  if (NS_FAILED(rv))
    return rv;

  mCurrentSize = size; 
  return NS_OK;
}