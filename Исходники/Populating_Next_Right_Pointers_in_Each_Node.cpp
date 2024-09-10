int main() {
    #define N new TreeLinkNode
    TreeLinkNode *tree =  N(0,
                            N(1,N(3),N(4)),
                            N(2,N(5),N(6)));
    Solution s;
    s.connect(tree);
    cout<<"[\n";
    for (auto level : s.levelOrder(tree)) {
        cout<<"  [";
        for(auto e : level) 
            cout<<e<<" ";
        cout<<"]\n";
    }
    cout<<"]\n";

    return 0;
}