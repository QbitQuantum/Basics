int main()
{
    vector<int> vals = {10,7,6,5,8,9,15,12,13,17,16};
    TreeLinkNode* root = createTree(vals);
    Solution s;
    cout<<endl;
    vector<vector<int>> level;
    s.connect(root);
    for(auto&e : level)

    /**your code...*/
    destoryTree(root);
    return 0;

}