void heterozygote (unsigned r, unsigned c, COUNTTYPE * R)
{
    if(tableCount < 0) return;  // aborted because of time limit
	COUNTTYPE *res, *resn;
	int lower, upper;
	unsigned ntables;
	unsigned i, arc, ar1, ar2, a32, a31;
	COUNTTYPE * Rnew = R + nAlleles;
	double countsSoFar;
    unsigned long long hash;
    //	NSNumber * n;
	
    res = R-1; // to make res a 1-based version of R
    resn = Rnew-1; // so resn is 1-based for Rnew
	lower = res[r];
	for (i = 1; i < c; i++) lower -= res[i];
    lower = fmax(0, lower);
    upper = fmin(res[r], res[c]);
    if(c > 2) for (arc = lower; arc <= upper; arc++) {
        memcpy(Rnew, R, Rbytes); // Put a fresh set of residuals from R into Rnew
        
        // decrement residuals for the current value of arc.
        resn[r] -= arc;
        resn[c] -= arc;
        heterozygote(r, c-1, Rnew);
    }
	if(c==2){
		if(r > 3) for (ar2= lower; ar2 <= upper; ar2++) {
            memcpy(Rnew, R, Rbytes); // Put a fresh set of residuals from R into Rnew
    // decrement residuals for the current value of arc.
			resn[r] -= ar2;
			resn[c] -= ar2;
			// The value of ar1 is now fixed, so no need for any more calls to heterozygote in this row
			ar1 = fmin(resn[r], resn[1]);
			resn[1] -= ar1;
			resn[r] -= ar1;
            // Before calling homozygote, see if we have visited this node before by comparing its hash tag.
            hash = makeHash(r-1, Rnew);
            i = 0;
            // Search list of old nodes
            while (hash != nodez[i].hash && i < nextNode) i++;
            if(i < nextNode) {
				// old node was found, no need to go any further.
				tableCount += nodez[i].count;
			} else {
				// new node
				countsSoFar =  tableCount;
                homozygote(r-1, Rnew);
                if (nextNode < MAXNODE) {
                    // Make a new node
                    nodez[i].hash = hash;
                    nodez[i].count = tableCount - countsSoFar;
                    nextNode++;
                }
  			} // new node
        }
		if(r==3) // and c = 2, then we can handle a series of two-allele cases with no deeper recursion
		{
			for(a32 = lower; a32 <= upper; a32++) {
				a31 = fmin(res[1], res[3]-a32); //Value of a31 is now fixed for each a32
				ntables = (fmin(res[1] - a31, res[2]-a32))/2 + 1;
				tableCount += ntables;
			}
		} // if r == 3
	} // if c == 2
} // heterozygote