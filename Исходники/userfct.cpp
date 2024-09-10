/* ----------------------------------------------------------- */
void ValueUpdate(PegPrompt* pObject, int iValue)
{
	PEGCHAR tStringToDisplay[5];
	long lValue = 0;

	lValue = iValue;

	_ltoa(lValue,tStringToDisplay,10);

	pObject->DataSet(tStringToDisplay);
	pObject->Invalidate();
	pObject->Parent()->Draw();
}