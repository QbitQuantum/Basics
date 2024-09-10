int main()
{
    int data1[] = {5,3,2,4,8,7,9};
    int data2[] = {2,3,4,5,7,8,9};
    int n1 = sizeof(data1)/sizeof(data1[0]);
    int n2 = sizeof(data2)/sizeof(data2[0]);
    vector<int> preorder(data1,data1+n1);
    vector<int> inorder(data2, data2+n2);
    TreeLinkNode* root = buildTree(preorder,inorder);
    Solution solution;
    solution.connect(root);
}