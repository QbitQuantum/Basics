int _tmain(int argc, _TCHAR* argv[])
{

	HashSet myHashSet;
	for (int i=0; i<30; i++)
	{
		myHashSet.insert(i);
	}

	cout<<"The HashSet:"<<endl;
	myHashSet.printHashSet(cout);
	cout<<"The number 0 exists?"<<"\t"<<myHashSet.exists(0)<<endl;
	cout<<"The number 30 exists?"<<"\t"<<myHashSet.exists(30)<<endl;
	cout<<"insert 40:"<<myHashSet.insert(40)<<endl;
	myHashSet.printHashSet(cout);
	cout<<"insert 10:"<<myHashSet.insert(10)<<endl;
	myHashSet.printHashSet(cout);
	cout<<"delete 40:"<<myHashSet.remove(40)<<endl;
	myHashSet.printHashSet(cout);
	cout<<"delete 50:"<<myHashSet.remove(50)<<endl;
	myHashSet.printHashSet(cout);

	return 0;
}