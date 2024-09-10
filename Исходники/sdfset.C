// if ELM is the next thing to return, then forget about it and advance the
// iterator to the next element. This is a useful method to call when we are
// deleting elements from a set while iterating them at the same time.
void sdfsetPrevElmtIterator::skip(sdfsetElmt* elm)
{
   if (currentelmt == elm)
      operator()();
}