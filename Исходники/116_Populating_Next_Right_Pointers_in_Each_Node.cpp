void main(){
    TreeLinkNode n1(1),n2(2),n3(3),n4(4);
    n1.left = &n2;
    n1.right = &n3;
   // n2.left = &n4;
    Solution sol;
    sol.connect(&n1);
}