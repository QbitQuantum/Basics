    void StrandSplit::Split::split<false>(size_t threadIndex, size_t threadCount, LockStepTaskScheduler* scheduler, PrimRefBlockAlloc<BezierPrim>& alloc, 
					  BezierRefList& prims, 
					  BezierRefList& lprims_o, PrimInfo& linfo_o, 
					  BezierRefList& rprims_o, PrimInfo& rinfo_o) const 
    {
      BezierRefList::item* lblock = lprims_o.insert(alloc.malloc(threadIndex));
      BezierRefList::item* rblock = rprims_o.insert(alloc.malloc(threadIndex));
      linfo_o.reset();
      rinfo_o.reset();
      
      while (BezierRefList::item* block = prims.take()) 
      {
	for (size_t i=0; i<block->size(); i++) 
	{
	  const BezierPrim& prim = block->at(i); 
	  const Vec3fa axisi = normalize(prim.p3-prim.p0);
	  const float cos0 = abs(dot(axisi,axis0));
	  const float cos1 = abs(dot(axisi,axis1));
	  
	  if (cos0 > cos1) 
	  {
	    linfo_o.add(prim.bounds(),prim.center());
	    if (likely(lblock->insert(prim))) continue; 
	    lblock = lprims_o.insert(alloc.malloc(threadIndex));
	    lblock->insert(prim);
	  } 
	  else 
	  {
	    rinfo_o.add(prim.bounds(),prim.center());
	    if (likely(rblock->insert(prim))) continue;
	    rblock = rprims_o.insert(alloc.malloc(threadIndex));
	    rblock->insert(prim);
	  }
	}
	alloc.free(threadIndex,block);
      }
    }