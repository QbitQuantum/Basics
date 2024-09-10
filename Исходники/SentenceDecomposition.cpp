double test3() {
	string p0 = "ommwreehisymkiml";
	string t1[] = {"we", "were", "here", "my", "is", "mom", "here", "si", "milk", "where", "si"};
	vector <string> p1(t1, t1+sizeof(t1)/sizeof(string));
	SentenceDecomposition * obj = new SentenceDecomposition();
	clock_t start = clock();
	int my_answer = obj->decompose(p0, p1);
	clock_t end = clock();
	delete obj;
	cout <<"Time: " <<(double)(end-start)/CLOCKS_PER_SEC <<" seconds" <<endl;
	int p2 = 10;
	cout <<"Desired answer: " <<endl;
	cout <<"\t" << p2 <<endl;
	cout <<"Your answer: " <<endl;
	cout <<"\t" << my_answer <<endl;
	if (p2 != my_answer) {
		cout <<"DOESN'T MATCH!!!!" <<endl <<endl;
		return -1;
	}
	else {
		cout <<"Match :-)" <<endl <<endl;
		return (double)(end-start)/CLOCKS_PER_SEC;
	}
}