    void SpatialSplit::Split::split<false>(size_t threadIndex, size_t threadCount, LockStepTaskScheduler* scheduler, PrimRefBlockAlloc<BezierPrim>& alloc, 
					   Scene* scene, BezierRefList& prims, 
					   BezierRefList& lprims_o, PrimInfo& linfo_o, 
					   BezierRefList& rprims_o, PrimInfo& rinfo_o) const
    {
      assert(valid());
      BezierRefList::item* lblock = lprims_o.insert(alloc.malloc(threadIndex));
      BezierRefList::item* rblock = rprims_o.insert(alloc.malloc(threadIndex));
      linfo_o.reset();
      rinfo_o.reset();

      while (BezierRefList::item* block = prims.take()) 
      {
	for (size_t i=0; i<block->size(); i++) 
	{
	  const BezierPrim& prim = block->at(i);
	  const int bin0 = mapping.bin(min(prim.p0,prim.p3))[dim];
	  const int bin1 = mapping.bin(max(prim.p0,prim.p3))[dim];
	  
	  /* sort to the left side */
	  if (bin0 < pos && bin1 < pos) // FIXME: optimize
	  {
	    linfo_o.add(prim.bounds(),prim.center());
	    if (likely(lblock->insert(prim))) continue; 
	    lblock = lprims_o.insert(alloc.malloc(threadIndex));
	    lblock->insert(prim);
	    continue;
	  }
	  
	  /* sort to the right side */
	  if (bin0 >= pos && bin1 >= pos)// FIXME: optimize
	  {
	    rinfo_o.add(prim.bounds(),prim.center());
	    if (likely(rblock->insert(prim))) continue;
	    rblock = rprims_o.insert(alloc.malloc(threadIndex));
	    rblock->insert(prim);
	    continue;
	  }
	  
	  /* split and sort to left and right */
	  BezierPrim left,right;
	  float fpos = mapping.pos(pos,dim);
	  if (prim.split(dim,fpos,left,right)) 
	  {
	    if (!left.bounds().empty()) {
	      linfo_o.add(left.bounds(),left.center());
	      if (!lblock->insert(left)) {
		lblock = lprims_o.insert(alloc.malloc(threadIndex));
		lblock->insert(left);
	      }
	    }
	    if (!right.bounds().empty()) {
	      rinfo_o.add(right.bounds(),right.center());
	      if (!rblock->insert(right)) {
		rblock = rprims_o.insert(alloc.malloc(threadIndex));
		rblock->insert(right);
	      }
	    }
	    continue;
	  }
	  
	  /* insert to left side as fallback */
	  linfo_o.add(prim.bounds(),prim.center());
	  if (!lblock->insert(prim)) {
	    lblock = lprims_o.insert(alloc.malloc(threadIndex));
	    lblock->insert(prim);
	  }
	}
	alloc.free(threadIndex,block);
      }
    }