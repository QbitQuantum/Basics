vector<Trust<int64_t> *> *Stoichastic::pickRandomTrusts(LLRB_Tree<Trust<int64_t> *, uint64_t> *tree, vector<Trust<int64_t> *> *originals, uint64_t requests) {
  
  LLRB_TreeNode<Trust<int64_t> *, uint64_t> *curr;
  LLRB_Tree<Trust<int64_t> *, uint64_t> randoms;
  vector<LLRB_TreeNode<Trust<int64_t> *, uint64_t> *> stack;
  uint64_t tmp;
  uint8_t leftDepth = 0, rightDepth = 0;
  int64_t pivot;
  
  curr = tree->treeRoot;
  
  while (curr != randoms.leftOf(curr)) {
    leftDepth++;
    curr = randoms.leftOf(curr);
  }
  
  curr = tree->treeRoot;
  
  while (curr != randoms.leftOf(curr)) {
    rightDepth++;
    curr = randoms.rightOf(curr);
  }
  
  pivot = (int64_t)leftDepth / ((int64_t)(leftDepth+rightDepth));
  
  if (originals != NULL) {
    for (uint64_t ix = 0; ix < originals->size(); ix++) {
      randoms.insert(originals->at(ix), (uint64_t)originals->at(ix));
    }
    
    originals->resize(0);
    delete originals;
    
  }
  
  for (uint64_t ix = 0; ix < requests; ix++) {
    curr = tree->treeRoot;
    
    while (curr != randoms.leftOf(curr)) {
      stack.push_back(curr);
      if ((rand() / (int64_t)RAND_MAX) < pivot) {
        curr = randoms.leftOf(curr);
      } else {
        curr = randoms.rightOf(curr);
      }
    }
    
    tmp = random() % (uint64_t)powl(2, stack.size());
    Trust<int64_t> *entry = stack[log2l(tmp)]->data;
    randoms.insert(entry, (uint64_t)entry);
    stack.resize(0);
  }
  
  return randoms.select(NULL, NULL);
}