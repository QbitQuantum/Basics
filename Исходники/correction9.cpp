bool IOF::correct(int pool, char* read, int direction, int pos, int kmerPos, unsigned short crtCset, vector<struct cset>& csets, const mybitsetx& e, mybitsetx c, unsigned short orient, HashTable<mysig>& pools2bacs, unsigned int& numSearch, unsigned int& numHit) {

unsigned int i;
bool correct=false;
unsigned short bacs[MAX_BACS];
unsigned short pools[POOLS];
unsigned int numBacs, numPools; 

mybitsetx g;
mybitsetx o(c);
c.invert();
if (c<o)
	g=c;
else
	g=o;

//DEBUG
//cout << "[correct]Searching " << g; 
if (!sh.searchCopy(g)) {
#if defined DEBUG
	cout << "[correct]kmer not found in the hashtable!" << endl;
#endif	
	return false;
}	

numPools=g.count(pools);
if (numPools<LOW) {
#if defined DEBUG
	cout << "[correct]no pools found " << numPools << endl;
#endif	
	return false;	
}

if (numPools>HIGH)
	correct=true;

numBacs=0;
if (numPools>=LOW&&numPools<=HIGH) {
	mysig sig(pools, numPools);
	if (!pools2bacs.searchCopy(sig)) { 
		trie.search(pools, numPools, bacs, numBacs);
		numSearch++;
		sig.setBacs(bacs, numBacs);
		pools2bacs.insert(sig);
	} else {
		numHit++;
	}
	numBacs=sig.getNumBacs();	
	for (unsigned int i=0;i<numBacs;i++)
		bacs[i]=sig.getBac(i);
	
	if (numBacs==0)	{
#if defined DEBUG
		cout << "[correct]no bacs found " << numBacs << endl;
		cout << "[correct]numPools " << numPools << ": ";
		for (unsigned int i=0;i<numPools;i++)
			cout << pools[i] << " ";
		cout << endl;	
#endif		
		return false;
	}
	
	//check that bacs found agree with other cset bacs
	bool hasBacs=false, found=false;
	for (auto it=csets.begin();it!=csets.end();it++) {
		if (it->bacs.size()==0)
			continue;
		
		hasBacs=true;
		
		found=false;
		for (unsigned int i=0;i<numBacs;i++) {//does this kmer belong to crt cset?
			if (it->bacs.find(bacs[i])!=it->bacs.end()) {
				found=true;
				break;
			}
		}

		if (found)
			break;
	};

	if (!hasBacs||found) {
		correct=true;
		for (i=0;i<numBacs;i++) 
			csets[crtCset].bacs.insert(bacs[i]);
	}	
	
}//if (numPools>=LOW&&numPools<=HIGH) {

#if defined DEBUG
cout << "[correct]Found " << g; 
cout << "[correct]numPools " << numPools << endl;
cout << "[correct]numBacs " << numBacs << ": ";
for (i=0;i<numBacs;i++) 
	cout << bacs[i] << ",";
cout << endl;
#endif

if (correct) {
	//extend crt cset
	if (direction==0)
		csets[crtCset].begin--;
	else	
		csets[crtCset].end++;
	//change base in read
	char newBase;
	char oldBase=read[pos];
	if (orient)
		newBase=o.getBase(kmerPos);
	else 
		newBase=mybitsetx::rev(o.getBase(kmerPos)); 
	read[pos]=newBase;
	//update pool counts in hashtable
	sh.searchUpdatePool(e, pool, -1);
	sh.searchUpdatePool(g, pool, 1);
	
#if defined DEBUG
	cout << "[correct]read pos " << pos << " old base " << oldBase << " new base " << newBase << endl;
	cout << "[correct]crtCset begin " << csets[crtCset].begin << " crtCset end " << csets[crtCset].end << endl << endl; 
#endif
	return true;
}//if (correct)
	
return false;

};