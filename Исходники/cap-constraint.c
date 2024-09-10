static int ApplyCap (TRI_cap_constraint_t* cap,
                     TRI_primary_collection_t* primary,
                     TRI_transaction_collection_t* trxCollection) {
  TRI_document_collection_t* document;
  TRI_headers_t* headers;
  size_t count;
  int res;

  document = (TRI_document_collection_t*) primary;
  headers = document->_headers;
  count = headers->count(headers);

  res = TRI_ERROR_NO_ERROR;

  while (count > cap->_size) {
    TRI_doc_mptr_t* oldest = headers->front(headers);

    if (oldest != NULL) {
      if (trxCollection != NULL) {
        res = TRI_DeleteDocumentDocumentCollection(trxCollection, NULL, oldest);
        
        if (res != TRI_ERROR_NO_ERROR) {
          LOG_WARNING("cannot cap collection: %s", TRI_errno_string(res));
          break;
        }
      }
      else {
        headers->unlink(headers, oldest);
      }

      count--;
    }
    else {
      // we should not get here
      LOG_WARNING("logic error in %s", __FUNCTION__);
      break;
    }
  }

  return res;
}