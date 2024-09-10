Node_t* leastCommonAncestor(Node_t* root, Node_t* node1, Node_t* node2) {
  // Both node1 and node2 belongs to left side.
  if (isChild(root->left, node1) && 
      isChild(root->left, node2))
    return leastCommonAncestor(root->left, node1, node2);
  // Both node1 and node2 belongs to right side.
  else if(isChild(root->right, node1)&&
          isChild(root->right, node2))
    return leastCommonAncestor(root->right, node1, node2);
  else
    return root;
}