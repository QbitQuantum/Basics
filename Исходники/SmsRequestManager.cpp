NS_IMETHODIMP
SmsRequestManager::NotifyNoMessageInList(PRInt32 aRequestId)
{
  SmsRequest* request = GetRequest(aRequestId);

  nsCOMPtr<nsIDOMMozSmsCursor> cursor = request->GetCursor();
  if (!cursor) {
    cursor = new SmsCursor();
  } else {
    static_cast<SmsCursor*>(cursor.get())->Disconnect();
  }

  return NotifySuccess<nsIDOMMozSmsCursor*>(aRequestId, cursor);
}