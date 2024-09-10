template <class VF> inline
Vector<Scalar>& Vector<Scalar>::applyBinaryFunctor(const VF& func,
  const Vector<Scalar>& other) 
{
  TimeMonitor t(*opTimer());

  TEUCHOS_TEST_FOR_EXCEPTION(!this->space().isCompatible(other.space()),
    std::runtime_error,
    "Spaces this=" << this->space() << " and other="
    << other.space() << " are not compatible in binary operation "
    << func.description());

  if (this->numBlocks() > 1)
  {
    for (int b=0; b<this->numBlocks(); b++)
    {
      Vector<Scalar> myBlock = this->getNonConstBlock(b);
      Vector<Scalar> yourBlock = other.getBlock(b);
      myBlock.applyBinaryFunctor(func, yourBlock);
    }
  }
  else
  {
    while(this->hasMoreChunks())
    {
      NonConstDataChunk<Scalar> myChunk = this->nextChunk();
      ConstDataChunk<Scalar> yourChunk = other.nextConstChunk();
      Scalar* me = myChunk.values();
      const Scalar* you = yourChunk.values();
      for (int i=0; i<myChunk.size(); i++)
      {
        me[i] = func(me[i], you[i]);
      }
    }
    other.rewind();
    this->rewind();
  }

  return *this;
}