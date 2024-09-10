static int ApplyCap (TRI_cap_constraint_t* cap,
                     TRI_document_collection_t* document,
                     TRI_transaction_collection_t* trxCollection) {

  TRI_headers_t* headers = document->_headersPtr;  // PROTECTED by trx in trxCollection
  size_t currentCount    = headers->count();
  int64_t currentSize    = headers->size();

  int res = TRI_ERROR_NO_ERROR;

  // delete while at least one of the constraints is still violated
  while ((cap->_count > 0 && currentCount > cap->_count) ||
         (cap->_size > 0 && currentSize > cap->_size)) {
    TRI_doc_mptr_t* oldest = headers->front();

    if (oldest != nullptr) {
      TRI_ASSERT(oldest->getDataPtr() != nullptr);  // ONLY IN INDEX, PROTECTED by RUNTIME
      size_t oldSize = ((TRI_df_marker_t*) (oldest->getDataPtr()))->_size;  // ONLY IN INDEX, PROTECTED by RUNTIME

      TRI_ASSERT(oldSize > 0);

      if (trxCollection != nullptr) {
        res = TRI_DeleteDocumentDocumentCollection(trxCollection, nullptr, oldest);

        if (res != TRI_ERROR_NO_ERROR) {
          LOG_WARNING("cannot cap collection: %s", TRI_errno_string(res));
          break;
        }
      }
      else {
        headers->unlink(oldest);
      }

      currentCount--;
      currentSize -= (int64_t) oldSize;
    }
    else {
      // we should not get here
      LOG_WARNING("logic error in %s", __FUNCTION__);
      break;
    }
  }

  return res;
}