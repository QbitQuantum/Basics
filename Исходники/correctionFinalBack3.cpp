bool correct(char* read, unsigned short direction, int crtKmer, int pos, int kmerPos, mybitsetx c, vector<mybitsetx>& kmersInHash, const vector<unsigned short>& orientation, vector<cset>& csets, unsigned short crtCset, unsigned int& numSearch, unsigned int& numHit) {

bool correct=false;
//mybitsetx e=kmers[crtKmer];
//mybitsetx e=kmersInHash[crtKmer];
unsigned short bacs[MAX_BACS];
unsigned short pools[POOLS];
unsigned short numBacs, numPools; 

unsigned short orient=orientation[crtKmer];

mybitsetx g;
mybitsetx o(c);
c.invert();
if (c<o)
	g=c;
else
	g=o;

//DEBUG
//cout << "[correct]Searching " << g; 
//#pragma omp critical
//{
if (!ioh->searchCopy(g)) {
//}
#if defined DEBUG
	cout << "[correct]kmer not found in the hashtable!" << endl;
#endif	
	return false;
};	

numPools=g.getPools(pools);
if (numPools<LOW) {
#if defined DEBUG
	cout << "[correct]No pools found " << numPools << endl;
#endif	
	return false;	
};

if (numPools>HIGH)
	correct=true;

numBacs=0;
if (numPools>=LOW&&numPools<=HIGH) {
	mysig sig(pools, numPools);
	if (!pools2bacs->searchCopy(sig)) { 
		trie->search(pools, numPools, bacs, numBacs);
		
		numSearch++;
		
		sig.setBacs(bacs, numBacs);
		#pragma omp critical (insert)
		{
		pools2bacs->insert(sig);
		}
	} else {
		numHit++;
	}
	numBacs=sig.getNumBacs();	
	for (unsigned short i=0;i<numBacs;i++)
		bacs[i]=sig.getBac(i);
	
	if (numBacs==0)	{
#if defined DEBUG
		cout << "[correct]No bacs found " << numBacs << endl;
		cout << "[correct]numPools " << numPools << ": ";
		for (unsigned short i=0;i<numPools;i++)
			cout << pools[i] << " ";
		cout << endl;	
#endif		
		return false;
	}
	
	bool hasBacs=false, found=false;
	//check that bacs found agree with other cset bacs
	//for (auto it=csets.begin();it!=csets.end();it++) {
	for (auto it=csets.begin();it!=csets.begin() + crtCset + 1;it++) {
		if (it->bacs.size()==0)
			continue;
			
		hasBacs=true;
		
		//found=false;
		for (unsigned short i=0;i<numBacs;i++) {//does this kmer belong to crt cset?
			if (it->bacs.find(bacs[i])!=it->bacs.end()) {
				found=true;
				break;
			}
		}
		
		if (found)
			break;
	}
	
	if (!hasBacs||found) {
		correct=true;
	} else {
#if defined DEBUG
		cout << "[correct]Bacs do not match: ";
		for (unsigned short i=0;i<numBacs;i++) 
			cout << bacs[i] << ",";
		cout << endl;
		return false;
#endif		
	}

	if (found) {
		set<unsigned short> newBacs;
		set<unsigned short> crtBacs=csets[crtCset].bacs;
		for (unsigned short i=0;i<numBacs;i++)
			if (crtBacs.find(bacs[i])!=crtBacs.end()) 
				newBacs.insert(bacs[i]);
		csets[crtCset].bacs=newBacs;		
	} else {
		csets[crtCset].bacs.insert(bacs, bacs + numBacs);
	}
	
}//if (numPools>=LOW&&numPools<=HIGH) {

#if defined DEBUG
cout << "[correct]Found " << g; 
cout << "[correct]numPools " << numPools << ": ";
for (unsigned short i=0;i<numPools;i++) 
	cout << pools[i] << ",";
cout << endl;
cout << "[correct]numBacs " << numBacs << ": ";
for (unsigned short i=0;i<numBacs;i++) 
	cout << bacs[i] << ",";
cout << endl;
#endif

if (correct) {
	
	//change base in read
	char newBase;
#if defined DEBUG
	char oldBase=read[pos];
#endif
	if (orient)
		newBase=o.getBase(kmerPos);
	else 
		newBase=mybitsetx::rev(o.getBase(kmerPos)); 
	
	read[pos]=newBase;
#if defined DEBUG
	cout << "[correct]read pos " << pos << " old base " << oldBase << " new base " << newBase << endl;
#endif
	
	//change original k-mer so that we can reverse pool counts in hash table if this correction turns out to be wrong and we have to backtrack
	kmersInHash[crtKmer]=g;
	
	if (direction==0) 
		csets[crtCset].begin--;
	else	
		csets[crtCset].end++;
	
#if defined DEBUG
	cout << "[correct]crt cset begin " << csets[crtCset].begin << ", crt cset end " << csets[crtCset].end << endl << endl; 
#endif
	
	return true;

}//if (correct)
	
return false;
};