//int main(int argc, char** argv)
int main()
{
	
	vector<Token> ex_list;
	//ex_list = sc.scan(argv[1]);
	ex_list = sc.scan("parcertest1.txt");
	//sc.scan("parcertest1.txt", "parceresport.txt");
	p.get_vector(ex_list);
	 
	DLP vect = p.datalogprogram("DLPEXPORT.txt");
	
	w.importDLP(vect);
	//string temp = argv[2];
	string temp = "a.txt";
	ofstream out(temp);
	w.doWork(out);
	w.factEval(out);
	w.printfacts(out);
	w.further_work(out);

	// out.close();


	//vector<Predicate> sh = vect.getSchemes();


	/*
	for (int i = 0; i < sh.size(); i++)
	{
		cout << sh[i].toString() << endl;
	}*/
	 
	
	//system("pause");
	return 0;
}