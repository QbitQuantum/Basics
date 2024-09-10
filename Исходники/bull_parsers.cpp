GetTreesOpts BullShell::ParseGetTrees(NexusToken& token ) const {
	errormsg.clear();
	if (kernel.getNumTaxa() == 0) {
		errormsg="You can't get trees without an active set of taxa";
		throw XBull( errormsg, token);
	}
	GetTreesOpts gto;
	bool readingMostRecent = false;
	gto.fromTree = -1;
	gto.toTree = -1;
	gto.mode = 7;
	std::string filePref;

	token.GetNextToken();
	while (token.GetToken()!=";") {
		if (token.Abbreviation("STOREBrlens")) {
			token.GetNextToken();
			gto.storeBrLensFromFile=true;
			if (token.GetToken() == "=") {
				token.GetNextToken();
				if (token.Abbreviation("No"))
					gto.storeBrLensFromFile=false;
				else if (!token.Abbreviation("Yes")) {
					errormsg="Expecting YES or NO after CurrentBranchLengths = option to LSCORE command";
					throw XBull(errormsg, token);
				}
			}
		}
		else if (token.Abbreviation("FRom")) {
			DemandEquals(token, "after From subcommand of GetTrees command");
			gto.fromTree = DemandPositiveInt(token, "after From subcommand of GetTrees command");
			if (gto.fromTree < 0) {
				errormsg="Expecting positive integer after FROM option of GETTREES";
				throw XBull(errormsg, token);
			}	
		}
		else if (token.Abbreviation("To")) {
			DemandEquals(token, "after To subcommand of GetTrees command");
			gto.toTree = DemandPositiveInt(token, "after To subcommand of GetTrees command");
			if (gto.toTree < 0) {
				errormsg="Expecting positive integer after TO option of GETTREES";
				throw XBull(errormsg, token);
			}	
		}
		else if (token.Abbreviation("REplace"))
			gto.mode=3;
		else if (token.Abbreviation("Mode")) {
			DemandEquals(token, "after Mode subcommand of GetTrees command");
			gto.mode = DemandPositiveInt(token, "after Mode subcommand of GetTrees command");
			if (gto.mode!=3 && gto.mode!=7) {
				errormsg="Right now bull only get trees with mode 3 or mode 7";
				throw XBull(errormsg, token);
			}	
		}
		else if (token.Abbreviation("FIle")) {
			DemandEquals(token, "after File subcommand of GetTrees command");
			token.GetNextToken();
			gto.filename = token.GetTokenReference();
		}
		else if (token.Abbreviation("PREfix")) {
			token.GetNextToken();
			if (token.GetToken() == "=")	
				token.GetNextToken();
			filePref = token.GetToken();
		}
		else if (token.Abbreviation("MOStrecent"))
			readingMostRecent=true;
		else {
			errormsg = "Unrecognized subcommand (";
			errormsg << token.GetTokenReference() << ") in GetTrees command.";
			throw XBull(errormsg, token);
		}
		token.GetNextToken();
	}
	
	if (readingMostRecent) {
		int highNum = GetHighestFileNum(filePref);
		if (highNum < 0) {
			errormsg << "Couldn't open file " << filePref << "0";
			throw XBull(errormsg, token);
		}  
		gto.filename = filePref;
		gto.filename += highNum;
	}
	if (gto.fromTree > -1 && gto.toTree > gto.fromTree) {
		errormsg << "The FromTree setting (" << gto.fromTree << ") cannot be less than the ToTree setting (" << gto.toTree << ")";
		throw XBull(errormsg, token);
	}
		
	gto.fromTree = (gto.fromTree < 1 ? -1 : gto.fromTree - 1);
	gto.toTree = (gto.toTree < 1 ? -1 : gto.toTree - 1);
	return gto;
}