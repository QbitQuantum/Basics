int main(){
    TreeLinkNode *root=new TreeLinkNode(5);
    TreeLinkNode *a=new TreeLinkNode(1);
    TreeLinkNode *b=new TreeLinkNode(3);
    TreeLinkNode *c=new TreeLinkNode(4);
    TreeLinkNode *d=new TreeLinkNode(6);
    TreeLinkNode *e=new TreeLinkNode(7);
    TreeLinkNode *f=new TreeLinkNode(9);
 
    root->left=b;
    //root->right=e;
     
    //b->left=a;
    //b->right=c;
 
    //e->left=d;
    //e->right=f;

	Solution s;

    s.connect(root);


    cout<<"results:"<<endl;
    TreeLinkNode* ptr=b;
    if(ptr->next!=NULL)
        cout<< ptr->next->val <<endl;
    else
        cout<<"NULL"<<endl;

	return 0;
}