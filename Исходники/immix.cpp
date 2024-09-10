  /**
   * Performs a garbage collection of the immix space.
   */
  void ImmixGC::collect(GCData& data) {
    Object* tmp;

    gc_.clear_lines();

    int via_handles_ = 0;
    int via_roots = 0;

    for(Roots::Iterator i(data.roots()); i.more(); i.advance()) {
      tmp = i->get();
      if(tmp->reference_p()) saw_object(tmp);
      via_roots++;
    }

    if(data.threads()) {
      for(std::list<ManagedThread*>::iterator i = data.threads()->begin();
          i != data.threads()->end();
          ++i) {
        scan(*i, false);
      }
    }

    for(capi::Handles::Iterator i(*data.handles()); i.more(); i.advance()) {
      if(i->in_use_p() && !i->weak_p()) {
        saw_object(i->object());
        via_handles_++;
      }
    }

    for(capi::Handles::Iterator i(*data.cached_handles()); i.more(); i.advance()) {
      if(i->in_use_p() && !i->weak_p()) {
        saw_object(i->object());
        via_handles_++;
      }
    }

    std::list<capi::Handle**>* gh = data.global_handle_locations();

    if(gh) {
      for(std::list<capi::Handle**>::iterator i = gh->begin();
          i != gh->end();
          ++i) {
        capi::Handle** loc = *i;
        if(capi::Handle* hdl = *loc) {
          if(!REFERENCE_P(hdl)) continue;
          if(hdl->valid_p()) {
            Object* obj = hdl->object();
            if(obj && obj->reference_p()) {
              saw_object(obj);
              via_handles_++;
            }
          } else {
            std::cerr << "Detected bad handle checking global capi handles\n";
          }
        }
      }
    }

#ifdef ENABLE_LLVM
    if(LLVMState* ls = data.llvm_state()) ls->gc_scan(this);
#endif

    gc_.process_mark_stack(allocator_);

    // We've now finished marking the entire object graph.

    check_finalize();

    // Finalize can cause more things to continue to live, so we must
    // check the mark_stack again.
    while(gc_.process_mark_stack(allocator_)) {
      check_finalize();
    }

    // Sweep up the garbage
    gc_.sweep_blocks();

    // This resets the allocator state to sync it up with the BlockAllocator
    // properly.
    allocator_.get_new_block();

    // Clear unreachable objects from the various remember sets
    int cleared = 0;
    unsigned int mark = object_memory_->mark();
    cleared = object_memory_->unremember_objects(mark);
    for(std::list<gc::WriteBarrier*>::iterator wbi = object_memory_->aux_barriers().begin();
        wbi != object_memory_->aux_barriers().end();
        ++wbi) {
      gc::WriteBarrier* wb = *wbi;
      cleared += wb->unremember_objects(mark);
    }

    // Now, calculate how much space we're still using.
    immix::Chunks& chunks = gc_.block_allocator().chunks();
    immix::AllBlockIterator iter(chunks);

    int live_bytes = 0;
    int total_bytes = 0;

    while(immix::Block* block = iter.next()) {
      total_bytes += immix::cBlockSize;
      live_bytes += block->bytes_from_lines();
    }

    double percentage_live = (double)live_bytes / (double)total_bytes;

    if(object_memory_->state()->shared.config.gc_immix_debug) {
      std::cerr << "[GC IMMIX: " << clear_marked_objects() << " marked"
                << ", "
                << via_roots << " roots "
                << via_handles_ << " handles "
                << (int)(percentage_live * 100) << "% live"
                << ", " << live_bytes << "/" << total_bytes
                << "]\n";
    }

    if(percentage_live >= 0.90) {
      if(object_memory_->state()->shared.config.gc_immix_debug) {
        std::cerr << "[GC IMMIX: expanding. "
                   << (int)(percentage_live * 100)
                   << "%]\n";
      }
      gc_.block_allocator().add_chunk();
    }

#ifdef IMMIX_DEBUG
    std::cout << "Immix: RS size cleared: " << cleared << "\n";

    immix::Chunks& chunks = gc_.block_allocator().chunks();
    std::cout << "chunks=" << chunks.size() << "\n";

    immix::AllBlockIterator iter(chunks);

    int blocks_seen = 0;
    int total_objects = 0;
    int total_object_bytes = 0;

    while(immix::Block* block = iter.next()) {
      blocks_seen++;
      std::cout << "block " << block << ", holes=" << block->holes() << " "
                << "objects=" << block->objects() << " "
                << "object_bytes=" << block->object_bytes() << " "
                << "frag=" << block->fragmentation_ratio()
                << "\n";

      total_objects += block->objects();
      total_object_bytes += block->object_bytes();
    }

    std::cout << blocks_seen << " blocks\n";
    std::cout << gc_.bytes_allocated() << " bytes allocated\n";
    std::cout << total_object_bytes << " object bytes / " << total_objects << " objects\n";

    int* holes = new int[10];
    for(int i = 0; i < 10; i++) {
      holes[i] = 0;
    }

    immix::AllBlockIterator iter2(chunks);

    while(immix::Block* block = iter2.next()) {
      int h = block->holes();
      if(h > 9) h = 9;

      holes[h]++;
    }

    std::cout << "== hole stats ==\n";
    for(int i = 0; i < 10; i++) {
      if(holes[i] > 0) {
        std::cout << i << ": " << holes[i] << "\n";
      }
    }

    delete[] holes;
    holes = NULL;
#endif
  }