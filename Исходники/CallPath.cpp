static void
overlayStaticStructure(Prof::CCT::ANode* node,
		       Prof::LoadMap::LM* loadmap_lm,
		       Prof::Struct::LM* lmStrct, BinUtil::LM* lm)
{
  // INVARIANT: The parent of 'node' has been fully processed
  // w.r.t. the given load module and lives within a correctly located
  // procedure frame.
  
  if (!node) { return; }

  bool useStruct = (!lm);

  // N.B.: dynamically allocate to better handle the deep recursion
  // required for very deep CCTs.
  StructToCCTMap* strctToCCTMap = new StructToCCTMap;

  if (0 && Analysis::CallPath::dbgOs) {
    (*Analysis::CallPath::dbgOs) << "overlayStaticStructure: node (";
    Prof::CCT::ADynNode* node_dyn = dynamic_cast<Prof::CCT::ADynNode*>(node);
    if (node_dyn) {
      (*Analysis::CallPath::dbgOs) << node_dyn->lmId() << ", " << hex << node_dyn->lmIP() << dec;
    }
    (*Analysis::CallPath::dbgOs) << "): " << node->toStringMe() << std::endl;
  }

  // ---------------------------------------------------
  // For each immediate child of this node...
  //
  // Use cmpByDynInfo()-ordering so that results are deterministic
  // (cf. hpcprof-mpi)
  // ---------------------------------------------------
  for (Prof::CCT::ANodeSortedChildIterator it(node, Prof::CCT::ANodeSortedIterator::cmpByDynInfo);
       it.current(); /* */) {
    Prof::CCT::ANode* n = it.current();
    it++; // advance iterator -- it is pointing at 'n'
    
    // ---------------------------------------------------
    // process Prof::CCT::ADynNode nodes
    // 
    // N.B.: Since we process w.r.t. one load module at a time, we may
    //   see non-ADynNode nodes!
    // ---------------------------------------------------
    Prof::CCT::ADynNode* n_dyn = dynamic_cast<Prof::CCT::ADynNode*>(n);
    if (n_dyn && (n_dyn->lmId() == loadmap_lm->id())) {
      using namespace Prof;

      const string* unkProcNm = NULL;
      if (n_dyn->isSecondarySynthRoot()) {
	unkProcNm = &Struct::Tree::PartialUnwindProcNm;
      }

      // 1. Add symbolic information to 'n_dyn'
      VMA lm_ip = n_dyn->lmIP();
      Struct::ACodeNode* strct =
	Analysis::Util::demandStructure(lm_ip, lmStrct, lm, useStruct,
					unkProcNm);
      
      n->structure(strct);
      //strct->demandMetric(CallPath::Profile::StructMetricIdFlg) += 1.0;

      DIAG_MsgIf(0, "overlayStaticStructure: dyn (" << n_dyn->lmId() << ", " << hex << lm_ip << ") --> struct " << strct << dec << " " << strct->toStringMe());
      if (0 && Analysis::CallPath::dbgOs) {
	(*Analysis::CallPath::dbgOs) << "dyn (" << n_dyn->lmId() << ", " << hex << lm_ip << dec << ") --> struct " << strct->toStringMe() << std::endl;
      }

      // 2. Demand a procedure frame for 'n_dyn' and its scope within it
      Struct::ANode* scope_strct = strct->ancestor(Struct::ANode::TyLoop,
						   Struct::ANode::TyAlien,
						   Struct::ANode::TyProc);
      //scope_strct->demandMetric(CallPath::Profile::StructMetricIdFlg) += 1.0;

      Prof::CCT::ANode* scope_frame =
	demandScopeInFrame(n_dyn, scope_strct, *strctToCCTMap);

      // FIXME: currently, this breaks prof-mpi with these messages:
      // Prof::CCT::ANodeSortedIterator::cmpByDynInfo: cannot compare
      // CCT::ANode::mergeDeep: adding not permitted
#if 0
      clipDuplicateContext(scope_frame, n);
#endif

      // 3. Link 'n' to its parent
      n->unlink();
      n->link(scope_frame);
    }
    
    // ---------------------------------------------------
    // recur
    // ---------------------------------------------------
    if (!n->isLeaf()) {
      overlayStaticStructure(n, loadmap_lm, lmStrct, lm);
    }
  }

  delete strctToCCTMap;
}