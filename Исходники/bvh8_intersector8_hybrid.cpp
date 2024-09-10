    void BVH8Intersector8Hybrid<PrimitiveIntersector8>::occluded(bool8* valid_i, BVH8* bvh, Ray8& ray)
    {
      /* load ray */
      const bool8 valid = *valid_i;
      bool8 terminated = !valid;
      Vec3f8 ray_org = ray.org, ray_dir = ray.dir;
      float8 ray_tnear = ray.tnear, ray_tfar  = ray.tfar;
      const Vec3f8 rdir = rcp_safe(ray_dir);
      const Vec3f8 org(ray_org), org_rdir = org * rdir;
      ray_tnear = select(valid,ray_tnear,float8(pos_inf));
      ray_tfar  = select(valid,ray_tfar ,float8(neg_inf));
      const float8 inf = float8(pos_inf);
      Precalculations pre(valid,ray);

      /* compute near/far per ray */
      Vec3i8 nearXYZ;
      nearXYZ.x = select(rdir.x >= 0.0f,int8(0*(int)sizeof(float8)),int8(1*(int)sizeof(float8)));
      nearXYZ.y = select(rdir.y >= 0.0f,int8(2*(int)sizeof(float8)),int8(3*(int)sizeof(float8)));
      nearXYZ.z = select(rdir.z >= 0.0f,int8(4*(int)sizeof(float8)),int8(5*(int)sizeof(float8)));

      /* allocate stack and push root node */
      float8    stack_near[stackSizeChunk];
      NodeRef stack_node[stackSizeChunk];
      stack_node[0] = BVH8::invalidNode;
      stack_near[0] = inf;
      stack_node[1] = bvh->root;
      stack_near[1] = ray_tnear; 
      NodeRef* stackEnd = stack_node+stackSizeChunk;
      NodeRef* __restrict__ sptr_node = stack_node + 2;
      float8*    __restrict__ sptr_near = stack_near + 2;

      while (1)
      {
        /* pop next node from stack */
        assert(sptr_node > stack_node);
        sptr_node--;
        sptr_near--;
        NodeRef cur = *sptr_node;
        if (unlikely(cur == BVH8::invalidNode)) {
          assert(sptr_node == stack_node);
          break;
        }

        /* cull node if behind closest hit point */
        float8 curDist = *sptr_near;
        const bool8 active = curDist < ray_tfar;
        if (unlikely(none(active))) 
          continue;
        
        /* switch to single ray traversal */
#if !defined(__WIN32__) || defined(__X86_64__)
        size_t bits = movemask(active);
        if (unlikely(__popcnt(bits) <= SWITCH_THRESHOLD)) {
          for (size_t i=__bsf(bits); bits!=0; bits=__btc(bits,i), i=__bsf(bits)) {
            if (occluded1(bvh,cur,i,pre,ray,ray_org,ray_dir,rdir,ray_tnear,ray_tfar,nearXYZ))
              terminated[i] = -1;
          }
          if (all(terminated)) break;
          ray_tfar = select(terminated,float8(neg_inf),ray_tfar);
          continue;
        }
#endif
                
        while (1)
        {
          /* test if this is a leaf node */
          if (unlikely(cur.isLeaf()))
            break;
          
          const bool8 valid_node = ray_tfar > curDist;
          STAT3(shadow.trav_nodes,1,popcnt(valid_node),8);
          const Node* __restrict__ const node = (Node*)cur.node();
          
          /* pop of next node */
          assert(sptr_node > stack_node);
          sptr_node--;
          sptr_near--;
          cur = *sptr_node;
          curDist = *sptr_near;
          
          for (unsigned i=0; i<BVH8::N; i++)
          {
            const NodeRef child = node->children[i];
            if (unlikely(child == BVH8::emptyNode)) break;
            
#if defined(__AVX2__)
            const float8 lclipMinX = msub(node->lower_x[i],rdir.x,org_rdir.x);
            const float8 lclipMinY = msub(node->lower_y[i],rdir.y,org_rdir.y);
            const float8 lclipMinZ = msub(node->lower_z[i],rdir.z,org_rdir.z);
            const float8 lclipMaxX = msub(node->upper_x[i],rdir.x,org_rdir.x);
            const float8 lclipMaxY = msub(node->upper_y[i],rdir.y,org_rdir.y);
            const float8 lclipMaxZ = msub(node->upper_z[i],rdir.z,org_rdir.z);
            const float8 lnearP = maxi(maxi(mini(lclipMinX, lclipMaxX), mini(lclipMinY, lclipMaxY)), mini(lclipMinZ, lclipMaxZ));
            const float8 lfarP  = mini(mini(maxi(lclipMinX, lclipMaxX), maxi(lclipMinY, lclipMaxY)), maxi(lclipMinZ, lclipMaxZ));
            const bool8 lhit   = maxi(lnearP,ray_tnear) <= mini(lfarP,ray_tfar);      
#else
            const float8 lclipMinX = (node->lower_x[i] - org.x) * rdir.x;
            const float8 lclipMinY = (node->lower_y[i] - org.y) * rdir.y;
            const float8 lclipMinZ = (node->lower_z[i] - org.z) * rdir.z;
            const float8 lclipMaxX = (node->upper_x[i] - org.x) * rdir.x;
            const float8 lclipMaxY = (node->upper_y[i] - org.y) * rdir.y;
            const float8 lclipMaxZ = (node->upper_z[i] - org.z) * rdir.z;
            const float8 lnearP = max(max(min(lclipMinX, lclipMaxX), min(lclipMinY, lclipMaxY)), min(lclipMinZ, lclipMaxZ));
            const float8 lfarP  = min(min(max(lclipMinX, lclipMaxX), max(lclipMinY, lclipMaxY)), max(lclipMinZ, lclipMaxZ));
            const bool8 lhit   = max(lnearP,ray_tnear) <= min(lfarP,ray_tfar);      
#endif
            
            /* if we hit the child we choose to continue with that child if it 
               is closer than the current next child, or we push it onto the stack */
            if (likely(any(lhit)))
            {
              assert(sptr_node < stackEnd);
              assert(child != BVH8::emptyNode);
              const float8 childDist = select(lhit,lnearP,inf);
              sptr_node++;
              sptr_near++;
              
              /* push cur node onto stack and continue with hit child */
              if (any(childDist < curDist))
              {
                *(sptr_node-1) = cur;
                *(sptr_near-1) = curDist; 
                curDist = childDist;
                cur = child;
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
        if (unlikely(cur == BVH8::invalidNode)) {
          assert(sptr_node == stack_node);
          break;
        }
        
        /* intersect leaf */
	assert(cur != BVH8::emptyNode);
        const bool8 valid_leaf = ray_tfar > curDist;
        STAT3(shadow.trav_leaves,1,popcnt(valid_leaf),8);
        size_t items; const Triangle* prim = (Triangle*) cur.leaf(items);
        terminated |= PrimitiveIntersector8::occluded(!terminated,pre,ray,prim,items,bvh->scene);
        if (all(terminated)) break;
        ray_tfar = select(terminated,float8(neg_inf),ray_tfar);
      }
      store8i(valid & terminated,&ray.geomID,0);
      AVX_ZERO_UPPER();
    }