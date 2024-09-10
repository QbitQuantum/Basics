int main(){
	int n, x;
	vector<int> nums;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> x;
		nums.push_back(x);
	}
	TreeLinkNode *root = buildTree(nums);
	preorderOutput(root);
	cout << endl;
	Solution sc;
	sc.connect(root);
	preorderOutput(root);
	cout << endl;
	levelOutput(root);
	return 0;
}