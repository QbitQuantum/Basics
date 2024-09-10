void
ANode::pruneByMetrics()
{
  for (ANodeChildIterator it(this); it.Current(); /* */) {
    ANode* x = it.current();
    it++; // advance iterator -- it is pointing at 'x'

    if (x->hasMetrics()) {
      x->pruneByMetrics();
    }
    else {
      x->unlink(); // unlink 'x' from tree
      delete x;
    }
  }
}