int _tmain(int argc, _TCHAR* argv[])
{
	/* test data, tree like :
	__________1
	________/   \
	_______2     3
	________\     \
	_________5     7
	*/
	TreeLinkNode n1(1);
	TreeLinkNode n2(2);
	TreeLinkNode n3(3);
	TreeLinkNode n5(5);
	TreeLinkNode n7(7);
	n1.left = &n2;
	n1.right = &n3;
	n2.right = &n5;
	n3.right = &n7;

	/* call function and print the result */
	Solution sln;
	sln.connect(&n1);

	return 0;
}