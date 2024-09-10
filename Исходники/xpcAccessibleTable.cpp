NS_IMETHODIMP
xpcAccessibleTable::GetSelectedCells(nsIArray** aSelectedCells)
{
  NS_ENSURE_ARG_POINTER(aSelectedCells);
  *aSelectedCells = nullptr;

  if (!Intl())
    return NS_ERROR_FAILURE;

  nsresult rv = NS_OK;
  nsCOMPtr<nsIMutableArray> selCells =
    do_CreateInstance(NS_ARRAY_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  AutoTArray<Accessible*, XPC_TABLE_DEFAULT_SIZE> cellsArray;
  Intl()->SelectedCells(&cellsArray);

  uint32_t totalCount = cellsArray.Length();
  for (uint32_t idx = 0; idx < totalCount; idx++) {
    Accessible* cell = cellsArray.ElementAt(idx);
    selCells->AppendElement(static_cast<nsIAccessible*>(ToXPC(cell)));
  }

  NS_ADDREF(*aSelectedCells = selCells);
  return NS_OK;
}