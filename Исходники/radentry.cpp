int CALL RadTrfTrsl(int* n, double* pV)
{
	Translation(pV[0], pV[1], pV[2]);

	*n = ioBuffer.OutInt();
	return ioBuffer.OutErrorStatus();
}