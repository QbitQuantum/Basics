/*!
	Called when MATRIX command needs to be parsed from within the UNALIGNED block. Deals with everything after the
	token MATRIX up to and including the semicolon that terminates the MATRIX command.
*/
void NxsUnalignedBlock::HandleMatrix(
  NxsToken & token)	/* is the token used to read from `in' */
	{
	if (taxa == NULL)
		{
		AssureTaxaBlock(false, token, "Matrix");
		unsigned ntax = taxa->GetNTax();
		if (ntax == 0)
			{
			errormsg = "Must precede ";
			errormsg += NCL_BLOCKTYPE_ATTR_NAME;
			errormsg += " block with a TAXA block or specify NEWTAXA and NTAX in the DIMENSIONS command";
			throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
			}
		}
	const unsigned ntax = taxa->GetNTax();
	uMatrix.clear();
	uMatrix.resize(ntax);
	unsigned indOfTaxInMemory = 0;
	std::vector<unsigned> toInMem(nTaxWithData, UINT_MAX);
	const unsigned ntlabels = taxa->GetNumTaxonLabels();
	errormsg.clear();
	bool taxaBlockNeedsLabels = (ntlabels == 0);
	if (!taxaBlockNeedsLabels && ntlabels < nTaxWithData)
		{
		errormsg << "Not enough taxlabels are known to read characters for " << nTaxWithData << " taxa in the Matrix command.";
		throw NxsException(errormsg, token);
		}
	for (unsigned indOfTaxInCommand = 0; indOfTaxInCommand < nTaxWithData; indOfTaxInCommand++)
		{
		NxsString nameStr;
		if (labels)
			{
			token.GetNextToken();
			nameStr = token.GetToken();
			if (taxaBlockNeedsLabels)
				{
				if (taxa->IsAlreadyDefined(nameStr))
					{
					errormsg << "Data for this taxon (" << nameStr << ") has already been saved";
					throw NxsException(errormsg, token);
					}
				try {
					indOfTaxInMemory = taxa->AddTaxonLabel(nameStr);
					}
				catch (NxsException &x)
					{
					if (nameStr == ";")
						{
						errormsg << "Unexpected ; after only " << indOfTaxInCommand << " taxa were read (expecting characters for " << nTaxWithData << " taxa).";
						throw NxsException(errormsg, token);
						}
					x.addPositionInfo(token);
					throw x;
					}
				}
			else
				{
				unsigned numOfTaxInMemory = taxa->TaxLabelToNumber(nameStr);
				if (numOfTaxInMemory == 0)
					{
					if (token.Equals(";"))
						errormsg << "Unexpected ;";
					else
						errormsg << "Could not find taxon named " << nameStr << " among stored taxon labels";
					throw NxsException(errormsg, token.GetFilePosition(), token.GetFileLine(), token.GetFileColumn());
					}
				indOfTaxInMemory = numOfTaxInMemory - 1;
				}
			}
		else
			{
			indOfTaxInMemory = indOfTaxInCommand;
			nameStr << 1+indOfTaxInMemory;
			}
		if (toInMem[indOfTaxInCommand] != UINT_MAX)
			{
			errormsg << "Characters for taxon " << indOfTaxInCommand << " (" << taxa->GetTaxonLabel(indOfTaxInMemory) << ") have already been stored";
			throw NxsException(errormsg, token);
			}
		toInMem[indOfTaxInCommand] = indOfTaxInMemory;
		NxsDiscreteStateRow * new_row = &uMatrix[indOfTaxInMemory];
		unsigned charInd = 0;
		while (HandleNextState(token, indOfTaxInMemory, charInd, *new_row, nameStr))
			charInd++;
		}
	}