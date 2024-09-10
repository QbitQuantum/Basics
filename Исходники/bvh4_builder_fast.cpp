    void BVH4BuilderFast::createLeaf(BuildRecord& current, Allocator& nodeAlloc, Allocator& leafAlloc, size_t threadIndex, size_t threadCount)
    {
#if defined(DEBUG)
      if (current.depth > BVH4::maxBuildDepthLeaf) 
        throw std::runtime_error("ERROR: depth limit reached");
#endif
      
      /* create leaf for few primitives */
      if (current.items() <= QBVH_BUILDER_LEAF_ITEM_THRESHOLD) {
        createSmallLeaf(this,current,leafAlloc,threadIndex);
        return;
      }
      
      /* first split level */
      BuildRecord record0, record1;
      split_fallback(prims,current,record0,record1);
      
      /* second split level */
      BuildRecord children[4];
      split_fallback(prims,record0,children[0],children[1]);
      split_fallback(prims,record1,children[2],children[3]);

      /* allocate node */
      Node* node = (Node*) nodeAlloc.malloc(sizeof(Node)); node->clear();
      *(NodeRef*)current.parentNode = bvh->encodeNode(node);
      
      /* recurse into each child */
      for (size_t i=0; i<4; i++) 
      {
        node->set(i,children[i].bounds.geometry);
        children[i].parentNode = (size_t)&node->child(i);
        children[i].depth = current.depth+1;
        createLeaf(children[i],nodeAlloc,leafAlloc,threadIndex,threadCount);
      }
      BVH4::compact(node); // move empty nodes to the end
    }