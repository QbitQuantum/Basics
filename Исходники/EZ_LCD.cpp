/****f* EZ.LCD.Wrapper/CEzLcd::SetProgressBarPosition
 * NAME
 *  HRESULT CEzLcd::SetProgressBarPosition -- Set position of the 
 *  progress bar's cursor
 * INPUTS
 *  handle          - handle to the object.
 *  percentage      - percentage of progress (0 to 100).
 * RETURN VALUE 
 *  E_FAIL if there was an error or if handle does not correspond to a
 *  progress bar.
 *  S_OK if no error.
 ******
 */
HRESULT CEzLcd::SetProgressBarPosition(HANDLE handle, FLOAT percentage)
{
	CLCDBase* myObject = GetObject(handle);

	if (NULL != myObject)
	{
		assert(LG_PROGRESS_BAR == myObject->GetObjectType());
        // only allow this function for progress bars
        if (LG_PROGRESS_BAR == myObject->GetObjectType())
        {
			CLCDProgressBar *progressBar = static_cast<CLCDProgressBar*>(myObject);
            assert(NULL != progressBar);
			progressBar->SetPos(percentage);
			return S_OK;
        }
	}

	return E_FAIL;
}