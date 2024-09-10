void CResponseHandler::RunL()
{
    // if any existing -> Send response
    if (iResponseArray.Count()) {
        CompleteAnyKey(iResponseArray[0]);
        // Remove already completed key
        iResponseArray.Remove(0);
        iResponseArray.Compress();
    }
}