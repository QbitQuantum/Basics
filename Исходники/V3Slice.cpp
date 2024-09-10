    // VISITORS
    virtual void visit(AstVarRef* nodep, AstNUser*) {
	// The LHS/RHS of an Assign may be to a Var that is an array. In this
	// case we need to create a slice across the entire Var
	if (m_assignp && !nodep->backp()->castArraySel()) {
	    pair<uint32_t,uint32_t> arrDim = nodep->varp()->dtypep()->dimensions(false);
	    uint32_t dimensions = arrDim.second;  // unpacked only
	    if (dimensions > 0) {
		AstVarRef* clonep = nodep->cloneTree(false);
		clonep->user1p(nodep);
		AstNode* newp = insertImplicit(clonep, 1, dimensions);
		nodep->replaceWith(newp); VL_DANGLING(nodep);
		newp->accept(*this);
	    }
	}
    }