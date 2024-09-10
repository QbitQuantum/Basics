EdgeStrip 
EdgeStrip::get_filtered(CSimplexFilter& filter) const
{
   EdgeStrip ret;
   for (int i=0; i<num(); i++)
      if (filter.accept(edge(i)))
         ret.add(vert(i), edge(i));
   return ret;
}