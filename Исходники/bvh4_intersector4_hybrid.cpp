    void BVH4Intersector4Hybrid<PrimitiveIntersector4>::occluded(sseb* valid_i, BVH4* bvh, Ray4& ray)
    {
      /* load ray */
      const sseb valid = *valid_i;
      sseb terminated = !valid;
      sse3f ray_org = ray.org, ray_dir = ray.dir;
      ssef ray_tnear = ray.tnear, ray_tfar  = ray.tfar;
#if defined(__FIX_RAYS__)
      const ssef float_range = 0.1f*FLT_MAX;
      ray_org = clamp(ray_org,sse3f(-float_range),sse3f(+float_range));
      ray_dir = clamp(ray_dir,sse3f(-float_range),sse3f(+float_range));
      ray_tnear = max(ray_tnear,FLT_MIN); 
      ray_tfar  = min(ray_tfar,float(inf)); 
#endif
      const sse3f rdir = rcp_safe(ray_dir);
      const sse3f org(ray_org), org_rdir = org * rdir;
      ray_tnear = select(valid,ray_tnear,ssef(pos_inf));
      ray_tfar  = select(valid,ray_tfar ,ssef(neg_inf));
      const ssef inf = ssef(pos_inf);
      
      /* allocate stack and push root node */
      ssef    stack_near[stackSizeChunk];
      NodeRef stack_node[stackSizeChunk];
      stack_node[0] = BVH4::invalidNode;
      stack_near[0] = inf;
      stack_node[1] = bvh->root;
      stack_near[1] = ray_tnear; 
      NodeRef* stackEnd = stack_node+stackSizeChunk;
      NodeRef* __restrict__ sptr_node = stack_node + 2;
      ssef*    __restrict__ sptr_near = stack_near + 2;
      
      while (1)
      {
        /* pop next node from stack */
        assert(sptr_node > stack_node);
        sptr_node--;
        sptr_near--;
        NodeRef curNode = *sptr_node;
        if (unlikely(curNode == BVH4::invalidNode)) {
          assert(sptr_node == stack_node);
          break;
        }

        /* cull node if behind closest hit point */
        ssef curDist = *sptr_near;
        const sseb active = curDist < ray_tfar;
        if (unlikely(none(active))) 
          continue;
        
        /* switch to single ray traversal */
#if !defined(__WIN32__) || defined(__X86_64__)
        size_t bits = movemask(active);
        if (unlikely(__popcnt(bits) <= SWITCH_THRESHOLD)) {
          for (size_t i=__bsf(bits); bits!=0; bits=__btc(bits,i), i=__bsf(bits)) {
            if (occluded1(bvh,curNode,i,ray,ray_org,ray_dir,rdir,ray_tnear,ray_tfar))
              terminated[i] = -1;
          }
          if (all(terminated)) break;
          ray_tfar = select(terminated,ssef(neg_inf),ray_tfar);
          continue;
        }
#endif

        while (1)
        {
          /* test if this is a leaf node */
          if (unlikely(curNode.isLeaf()))
            break;
          
          const sseb valid_node = ray_tfar > curDist;
          STAT3(shadow.trav_nodes,1,popcnt(valid_node),4);
          const Node* __restrict__ const node = curNode.node();
          
          /* pop of next node */
          assert(sptr_node > stack_node);
          sptr_node--;
          sptr_near--;
          curNode = *sptr_node;
          curDist = *sptr_near;
          
#pragma unroll(4)
          for (unsigned i=0; i<4; i++)
          {
            const NodeRef child = node->children[i];
            if (unlikely(child == BVH4::emptyNode)) break;
            
#if defined(__AVX2__)
            const ssef lclipMinX = msub(node->lower_x[i],rdir.x,org_rdir.x);
            const ssef lclipMinY = msub(node->lower_y[i],rdir.y,org_rdir.y);
            const ssef lclipMinZ = msub(node->lower_z[i],rdir.z,org_rdir.z);
            const ssef lclipMaxX = msub(node->upper_x[i],rdir.x,org_rdir.x);
            const ssef lclipMaxY = msub(node->upper_y[i],rdir.y,org_rdir.y);
            const ssef lclipMaxZ = msub(node->upper_z[i],rdir.z,org_rdir.z);
#else
            const ssef lclipMinX = (node->lower_x[i] - org.x) * rdir.x;
            const ssef lclipMinY = (node->lower_y[i] - org.y) * rdir.y;
            const ssef lclipMinZ = (node->lower_z[i] - org.z) * rdir.z;
            const ssef lclipMaxX = (node->upper_x[i] - org.x) * rdir.x;
            const ssef lclipMaxY = (node->upper_y[i] - org.y) * rdir.y;
            const ssef lclipMaxZ = (node->upper_z[i] - org.z) * rdir.z;
#endif
    
#if defined(__SSE4_1__)
            const ssef lnearP = maxi(maxi(mini(lclipMinX, lclipMaxX), mini(lclipMinY, lclipMaxY)), mini(lclipMinZ, lclipMaxZ));
            const ssef lfarP  = mini(mini(maxi(lclipMinX, lclipMaxX), maxi(lclipMinY, lclipMaxY)), maxi(lclipMinZ, lclipMaxZ));
            const sseb lhit   = maxi(lnearP,ray_tnear) <= mini(lfarP,ray_tfar);      
#else
            const ssef lnearP = max(max(min(lclipMinX, lclipMaxX), min(lclipMinY, lclipMaxY)), min(lclipMinZ, lclipMaxZ));
            const ssef lfarP  = min(min(max(lclipMinX, lclipMaxX), max(lclipMinY, lclipMaxY)), max(lclipMinZ, lclipMaxZ));
            const sseb lhit   = max(lnearP,ray_tnear) <= min(lfarP,ray_tfar);      
#endif
            
            /* if we hit the child we choose to continue with that child if it 
               is closer than the current next child, or we push it onto the stack */
            if (likely(any(lhit)))
            {
              assert(sptr_node < stackEnd);
              assert(child != BVH4::emptyNode);
              const ssef childDist = select(lhit,lnearP,inf);
              sptr_node++;
              sptr_near++;
              
              /* push cur node onto stack and continue with hit child */
              if (any(childDist < curDist))
              {
                *(sptr_node-1) = curNode;
                *(sptr_near-1) = curDist; 
                curDist = childDist;
                curNode = child;
              }
              
              /* push hit child onto stack */
              else {
                *(sptr_node-1) = child;
                *(sptr_near-1) = childDist; 
              }
            }	      
          }
        }
        
        /* return if stack is empty */
        if (unlikely(curNode == BVH4::invalidNode)) {
          assert(sptr_node == stack_node);
          break;
        }
        
        /* intersect leaf */
        const sseb valid_leaf = ray_tfar > curDist;
        STAT3(shadow.trav_leaves,1,popcnt(valid_leaf),4);
        size_t items; const Primitive* prim = (Primitive*) curNode.leaf(items);
        terminated |= PrimitiveIntersector4::occluded(!terminated,ray,prim,items,bvh->geometry);
        if (all(terminated)) break;
        ray_tfar = select(terminated,ssef(neg_inf),ray_tfar);
      }
      store4i(valid & terminated,&ray.geomID,0);
      AVX_ZERO_UPPER();
    }