void hal::validateSequence(const Sequence* sequence)
{
  // Verify that the DNA sequence doesn't contain funny characters
  DNAIteratorConstPtr dnaIt = sequence->getDNAIterator();
  hal_size_t length = sequence->getSequenceLength();
  for (hal_size_t i = 0; i < length; ++i)
  {
    char c = dnaIt->getChar();
    if (isNucleotide(c) == false)
    {
      stringstream ss;
      ss << "Non-nucleotide character discoverd at position " 
         << i << " of sequence " << sequence->getName() << ": " << c;
      throw hal_exception(ss.str());
    }
  }
  
  // Check the top segments
  if (sequence->getGenome()->getParent() != NULL)
  {
    hal_size_t totalTopLength = 0;
    TopSegmentIteratorConstPtr topIt = sequence->getTopSegmentIterator();
    hal_size_t numTopSegments = sequence->getNumTopSegments();
    for (hal_size_t i = 0; i < numTopSegments; ++i)
    {
      const TopSegment* topSegment = topIt->getTopSegment();
      validateTopSegment(topSegment);
      totalTopLength += topSegment->getLength();
      topIt->toRight();
    }
    if (totalTopLength != length)
    {
      stringstream ss;
      ss << "Sequence " << sequence->getName() << " has length " << length 
         << " but its top segments add up to " << totalTopLength;
      throw hal_exception(ss.str());
    }
  }

  // Check the bottom segments
  if (sequence->getGenome()->getNumChildren() > 0)
  {
    hal_size_t totalBottomLength = 0;
    BottomSegmentIteratorConstPtr bottomIt = 
       sequence->getBottomSegmentIterator();
    hal_size_t numBottomSegments = sequence->getNumBottomSegments();
    for (hal_size_t i = 0; i < numBottomSegments; ++i)
    {
      const BottomSegment* bottomSegment = bottomIt->getBottomSegment();
      validateBottomSegment(bottomSegment);
      totalBottomLength += bottomSegment->getLength();
      bottomIt->toRight();
    }
    if (totalBottomLength != length)
    {
      stringstream ss;
      ss << "Sequence " << sequence->getName() << " has length " << length 
         << " but its bottom segments add up to " << totalBottomLength;
      throw hal_exception(ss.str());
    }
  }
}