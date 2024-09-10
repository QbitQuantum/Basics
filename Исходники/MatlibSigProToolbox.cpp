CMatlibVector<CReal> Bartlett(const int iLen)
{
	const int iHalf = (int) Ceil((CReal) iLen / 2);
	CMatlibVector<CReal> fvHalfWin(iHalf);
	CMatlibVector<CReal> fvRet(iLen, VTY_TEMP);

	for (int i = 0; i < iHalf; i++)
		fvHalfWin[i] = (CReal) 2.0 * i / (iLen - 1);

	/* Build complete output vector depending on odd or even input length */
	if (iLen % 2)
		fvRet.Merge(fvHalfWin, fvHalfWin(iHalf - 1, -1, 1)); /* Odd */
	else
		fvRet.Merge(fvHalfWin, fvHalfWin(iHalf, -1, 1)); /* Even */

	return fvRet;
}