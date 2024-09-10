void CEnumInfo<T>::outEnumInfo(FILE **pOutFile, bool removeReportFile, const CGroupsInfo *pGroupInfo)
{
	setRunTime();
	FILE *outFile = pOutFile ? *pOutFile : NULL;
	if (!outFile)
		return;

	if (!pGroupInfo)
		pGroupInfo = this;

	pGroupInfo->printGroupInfo(outFile);
	const ulonglong nConstrMatr = constrCanonical();
	char buff[256];
	SPRINTF(buff, "\n%10llu matri%s" CONSTRUCTED_IN " ", nConstrMatr, nConstrMatr == 1 ? "x" : "ces");
	const size_t len = strlen(buff);
	convertTime(runTime(), buff + len, countof(buff) - len, false);
	outString(buff, outFile);

	const ulonglong nMatr = numbSimpleDesign();
	if (nConstrMatr > 0) {
		SPRINTF(buff, "%10llu matri%s ha%s no replicated blocks\n", nMatr, nMatr == 1 ? "x" : "ces", nMatr == 1 ? "s" : "ve");
		outString(buff, outFile);
	}

	SPRINTF(buff, "%10llu matri%s fully constructed\n", constrTotal(), constrTotal() == 1 ? "x was" : "ces were");
	outString(buff, outFile);

	outEnumInformation(pOutFile);
	if (removeReportFile) // Remove temporary file with the intermediate results	
		remove(reportFileName());
}