void FlipMemo::altCodes(const ResBlk& rblk,	bool useXplorNames, bool useOldNames, bool bbModel, 
						std::list<char>& sch) {
	char ch, buf[10];
	int rt = 0, k = 0, cursor = 0;
	bool isInResidueSet = FALSE, dupalt = FALSE;

	const char *resname = rblk.firstRec().resname();

	for(rt = 0; _resFlip[rt].rname; rt++) {
	        if ( (strcmp(_resFlip[rt].rname, resname) == 0)
	      		&& !(((_resFlip[rt].flags & USEOLDNAMES) && ! useOldNames)
	        	|| ((_resFlip[rt].flags & XPLORNAME)  && ! useXplorNames)
	        	|| ((_resFlip[rt].flags & USENEWNAMES) && (useOldNames || useXplorNames))) ) {
			isInResidueSet = TRUE;
			break; // residue type is one of those we are concerned with
		}
	}
	if (isInResidueSet) {
		std::multimap<std::string, PDBrec*> pdb = rblk.atomIt();
		std::string key;
		std::multimap<std::string, PDBrec*>::const_iterator pdbit = pdb.begin();
		PDBrec* atsq = NULL;
		while(pdbit != pdb.end()) {
			key = pdbit->first;
			for (; pdbit != pdb.end() && pdbit->first == key; ++pdbit) {
				atsq = pdbit->second;
				bool foundname = FALSE;
				for(int i=_resFlip[rt].fromScat;
				i < _resFlip[rt].fromScat+_resFlip[rt].numScat; i++) {

					if (strcmp(_pointName[rt][i], atsq->atomname()) == 0) {
						foundname = TRUE;
						break;
					}
				}
				if (foundname) {
					ch = toupper(atsq->alt());
					if (ch != ' ') {
						dupalt = FALSE;
						for(k = 0; k < cursor; k++) {
							if (ch == buf[k]) { dupalt = TRUE; break; }
						}
						if (! dupalt) {
							buf[cursor++] = ch;
						}
					}
				}
			}
		}
		if (cursor < 1) { sch.push_front(' '); } // no alt codes
		else {
			for(k = 0; k < cursor; k++) { // at least one alt code
				sch.push_front(buf[k]);
			}
		}
	}
}