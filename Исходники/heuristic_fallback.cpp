    FallBackSplit FallBackSplit::find(size_t threadIndex, PrimRefBlockAlloc<PrimRef>& alloc, PrimRefList& prims, 
				      PrimRefList& lprims_o, PrimInfo& linfo_o,
				      PrimRefList& rprims_o, PrimInfo& rinfo_o)
    {
      size_t num = 0;
      BBox3fa lbounds = empty, rbounds = empty;
      PrimRefList::item* lblock = lprims_o.insert(alloc.malloc(threadIndex));
      PrimRefList::item* rblock = rprims_o.insert(alloc.malloc(threadIndex));
      linfo_o.reset();
      rinfo_o.reset();

      while (PrimRefList::item* block = prims.take()) 
      {
	for (size_t i=0; i<block->size(); i++) 
	{
	  const PrimRef& prim = block->at(i); 
	  const BBox3fa bounds = prim.bounds();
	  
	  if ((num++)%2) 
	  {
	    linfo_o.add(bounds,prim.center2()); 
	    if (likely(lblock->insert(prim))) continue; 
	    lblock = lprims_o.insert(alloc.malloc(threadIndex));
	    lblock->insert(prim);
	  } 
	  else 
	  {
	    rinfo_o.add(bounds,prim.center2()); 
	    if (likely(rblock->insert(prim))) continue;
	    rblock = rprims_o.insert(alloc.malloc(threadIndex));
	    rblock->insert(prim);
	  }
	}
	alloc.free(threadIndex,block);
      }
      return FallBackSplit(linfo_o.geomBounds,linfo_o.size(),rinfo_o.geomBounds,rinfo_o.size());
    }