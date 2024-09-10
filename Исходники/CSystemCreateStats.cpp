void CSystemCreateStats::AddEntryPermutations (const CString &sPrefix, const TArray<CString> &Attribs, int iPos)

//	AddEntryPermutations
//
//	Adds permutions

	{
	//	If nothing, then nothing

	if (iPos >= Attribs.GetCount())
		return;

	//	Get the base case

	CString sNewPrefix;
	if (!sPrefix.IsBlank())
		sNewPrefix = strPatternSubst(CONSTLIT("%s,%s"), sPrefix, Attribs[iPos]);
	else
		sNewPrefix = Attribs[iPos];

	AddEntry(sNewPrefix);

	//	Permute with the base case

	AddEntryPermutations(sNewPrefix, Attribs, iPos + 1);

	//	Permute the remainder

	AddEntryPermutations(sPrefix, Attribs, iPos + 1);
	}