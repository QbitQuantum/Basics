//测试
int main()
{
    cout<<"树的双亲表示法"<<endl;
	Tree<char> newtree;
	int n;
	cout << "输入树节点数目：";
	cin >> n;
	newtree.CreatK(n);
	cout << "当没有对应数据输出，表示没有" << endl;
	cout << "第三个节点的树的值：" << newtree.GetData(3) << endl;
	cout << "第三个节点的最左子树根节点值：" << newtree.GetLeftMostChild(3, n) << endl;
	cout << "第三个节点的最右子树根节点值：" << newtree.GetRightMostChild(3, n) << endl;
	cout << "第三个节点的父亲节点值：" << newtree.GetParent(3) << endl;
	cout << "根节点值：" << newtree.GetRoot() << endl;
	getchar();
	return 0;
}