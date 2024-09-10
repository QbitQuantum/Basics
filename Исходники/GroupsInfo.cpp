void CGroupsInfo::printGroupInfo(FILE *file) const
{
	size_t i = GetAt(0)->numMatrices() ? 0 : 1;
	const size_t iMax = GetSize();
	if (i == iMax)
		return;			// Nothing was constructed

#define SHIFT "    "
	char buffer[256], line[256];
	size_t len = SPRINTF(buffer, "\n" SHIFT "    |Aut(D)|          Nd:             Ns:            Ndt:            Nst:\n");
	outString(buffer, file);

	strcpy_s(line, countof(line), SHIFT);
	const size_t l_Shift = strlen(SHIFT);
	memset(line + l_Shift, '_', len);
	len += l_Shift;
	strcpy_s(line + len, countof(line) - len, "\n");
	outString(line, file);

	COrderInfo total(0, 0);
	for (; i < iMax; i++) {
		const COrderInfo *pInfo = GetAt(i);
		total.addMatrix(pInfo);
		len = SPRINTF(buffer, SHIFT"%10zd", pInfo->groupOrder());
		pInfo->outNumbInfo(buffer, countof(buffer) - len, len);
		outString(buffer, file);
	}

	outString(line, file);
	len = SPRINTF(buffer, "        Total:");
	total.outNumbInfo(buffer, countof(buffer) - len, len);
	outString(buffer, file);
}