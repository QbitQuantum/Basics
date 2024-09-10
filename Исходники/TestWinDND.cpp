nsresult Do_CheckOneFile()
{
  nsresult rv;
  nsCOMPtr<nsITransferable> transferable;
  nsCOMPtr<nsISupportsArray> transferableArray;
  nsCOMPtr<nsISupports> genericWrapper;
  nsRefPtr<IDataObject> dataObj;
  rv = NS_NewISupportsArray(getter_AddRefs(transferableArray));
  if (NS_FAILED(rv)) {
    fail("Could not create the necessary nsISupportsArray");
    return rv;
  }

  rv = GetTransferableFile(transferable);
  if (NS_FAILED(rv)) {
    fail("Could not create the proper nsITransferable!");
    return rv;
  }
  genericWrapper = do_QueryInterface(transferable);
  rv = transferableArray->AppendElement(genericWrapper);
  if (NS_FAILED(rv)) {
    fail("Could not append element to transferable array");
    return rv;
  }

  rv = MakeDataObject(transferableArray, dataObj);
  if (NS_FAILED(rv)) {
    fail("Could not create data object");
    return rv;
  }

  FORMATETC fe;
  SET_FORMATETC(fe, CF_HDROP, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL);
  if (dataObj->QueryGetData(&fe) != S_OK) {
    fail("File data object does not support the file data type!");
    return NS_ERROR_UNEXPECTED;
  }

  STGMEDIUM* stg;
  stg = (STGMEDIUM*)CoTaskMemAlloc(sizeof(STGMEDIUM));
  if (dataObj->GetData(&fe, stg) != S_OK) {
    fail("File data object did not provide data on request");
    return NS_ERROR_UNEXPECTED;
  }

  rv = CheckValidHDROP(stg);
  if (NS_FAILED(rv)) {
    fail("HDROP was invalid");
    return rv;
  }

  ReleaseStgMedium(stg);

  return NS_OK;
}