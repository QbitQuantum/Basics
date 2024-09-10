/*
 this push override the parent one to order the node by descending H(c|t)
 */
void TrueBestFirstStack::push(Node* n, std::vector<unsigned int> &cand) {
	Scorer sc(db);
	std::vector<unsigned int> lsleft;
	std::vector<unsigned int> lsright;
	std::vector<unsigned int> set = n->getLS();
	std::vector<unsigned int> kcand;
	if (k > 0)
		kcand = Sampler::random(cand,k);
	else
		kcand = cand; 
	ScoreInfo si = sc.getBestScore(set,kcand);
	//fprintf(stderr,"TBF score: %f\n",si.score);
	//db->getLRSet(si,set,lsleft,lsright);
	double total = 0.0;
	for (int i = 0 ; i < set.size() ; ++i) {
		total += db->getWeight(set[i]);
	}
	n->setTest(si);
	if (si.score*total > 0.0) {
	db->getLRSet(si,set,lsleft,lsright);
	Node *left  = new Node();	left->setParent(n);
	left->setLS(lsleft);	n->setLeft(left);	
	Node *right = new Node();	right->setParent(n);
	right->setLS(lsright);	n->setRight(right);
	
		std::vector<double>::iterator it;
		std::vector< Node* >::iterator itn;
		for( it = values.begin(), itn = s.begin() ; it != values.end(); it++, itn++ )    {
			if (si.score*total <= *it) 
				break;
		}
		values.insert(it,si.score*total);
		//for (int i = 0 ; i < values.size() ; ++i)
		//	printf("%f|",values[i]);
		//printf("\n");
		n->setId(nbpush++);
		s.insert(itn,n);
		
		
	}
	
}