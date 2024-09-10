inline void
add_tracker(Bsimplex* s, CSimplexFilter& f, Bsimplex_list& ret)
{
   if (s && f.accept(s))
      ret.add_uniquely(s);
}