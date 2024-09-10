int main(int argc, char const *argv[])
{
	TreeLinkNode * root=new TreeLinkNode(2);
	root->left=new TreeLinkNode(1);
	root->right=new TreeLinkNode(3);
	root->left->left=new TreeLinkNode(0);
	root->left->right=new TreeLinkNode(7);
	root->right->left=new TreeLinkNode(9);
	root->right->right=new TreeLinkNode(1);
	root->left->left->left=new TreeLinkNode(2);
	// root->left->left->right=new TreeLinkNode(19);

	root->left->right->left=new TreeLinkNode(1);
	root->left->right->right=new TreeLinkNode(0);
	root->right->right->left=new TreeLinkNode(8);
	root->right->right->right=new TreeLinkNode(8);
	root->left->right->right->left=new TreeLinkNode(7);

	Solution so;
	so.connect(root);

	TreeLinkNode *p=root,*q;
	while(p!=NULL)
	{
		q=p;
		p=NULL;


		while(q!=NULL)
		{
			cout<<q->val<<'\t';
			if(p==NULL)
			{
				if(q->left!=NULL)
					p=q->left;
				else if(q->right!=NULL)
					p=q->right;			
			}
			q=q->next;
		}
		cout<<endl;
	}
	return 0;
}