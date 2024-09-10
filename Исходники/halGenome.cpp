void Genome::copySequence(Genome *dest) const
{
  DNAIteratorConstPtr inDna = getDNAIterator();
  DNAIteratorPtr outDna = dest->getDNAIterator();
  hal_size_t n = getSequenceLength();
  assert(n == dest->getSequenceLength());
  for (; (hal_size_t)inDna->getArrayIndex() < n; inDna->toRight(), 
         outDna->toRight())
  {
    outDna->setChar(inDna->getChar());
  }
}