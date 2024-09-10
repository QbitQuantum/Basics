int main(void)
{
	int n, N;
	int x;
	BinarySearchTree<int> bst;
	//bst.allowduplicates();
	cin>>N;
	
	cout<<"Insertions:"<<endl;
	n = N;
	while(n--)
	{
		cin>>x;
		bst.insert(x);
		bst.printtraversalinorder();
		cout<<"\t---"<<endl;
	}

	cout<<"\t---"<<endl;
	cout<<"\t---"<<endl;

	//ASSERT(false, "GG!");

	cout<<"Deletions:"<<endl;
	n = N;
	while(n--)
	{
		cin>>x;
		bst.remove(x, HARD);
		bst.printtraversalinorder();
		cout<<"\t---"<<endl;
	}
	//printtraversal1(bst.traversalinorder());
	//bst.printtraversalinorder();

	return 0;
}