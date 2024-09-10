int main() {
  BST<int>* bst = new BST<int>();

  bst->insert(10);
  bst->insert(5);
  bst->insert(15);
  bst->insert(13);
  bst->insert(17);
  bst->insert(16);
  bst->insert(18);
  bst->remove(15);

  // bst->print();
  bst->printTree();
  delete bst;
}