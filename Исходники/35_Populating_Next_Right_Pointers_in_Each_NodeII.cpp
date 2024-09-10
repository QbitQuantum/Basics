int main(){

	TreeLinkNode node1(1);
	TreeLinkNode node2(2);
	TreeLinkNode node3(3);
	TreeLinkNode node4(4);
	TreeLinkNode node5(5);
	node1.left=&node2;
	node1.left->left=&node4;
	node1.right=&node3;
	node1.right->right=&node5;
	Solution so;
	so.connect(&node1);
}