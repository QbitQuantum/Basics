    virtual void visit(AstArraySel* nodep, AstNUser*) {
	nodep->iterateChildren(*this);
	if (!nodep->user1Inc()) {
	    if (debug()==9) nodep->dumpTree(cout,"-in: ");
	    // Guard against reading/writing past end of arrays
	    AstNode* basefromp = AstArraySel::baseFromp(nodep->fromp());
	    int dimension      = AstArraySel::dimension(nodep->fromp());
	    int maxmsb = 0;
	    bool lvalue = false;
	    if (AstNodeVarRef* varrefp = basefromp->castNodeVarRef()) {
		AstArrayDType* adtypep = varrefp->varp()->dtypep()->dtypeDimensionp(dimension)->castArrayDType();
		if (!adtypep) nodep->v3fatalSrc("ArraySel to type without array at same depth");
		lvalue = varrefp->lvalue();
		maxmsb = adtypep->elementsConst()-1;
	    } else if (AstConst* lhconstp = basefromp->castConst()) {
		// If it's a PARAMETER[bit], then basefromp may be a constant instead of a varrefp
		maxmsb = lhconstp->width();
	    } else {
		nodep->v3fatalSrc("No VarRef or Const under ArraySel\n");
	    }
	    if (debug()>=9) nodep->dumpTree(cout,"arraysel_old: ");
	    V3Number widthnum (nodep->fileline(), nodep->bitp()->width(), maxmsb);

	    // See if the condition is constant true
	    AstNode* condp = new AstLte (nodep->fileline(),
					 nodep->bitp()->cloneTree(false),
					 new AstConst(nodep->fileline(), widthnum));
	    // Note below has null backp(); the Edit function knows how to deal with that.
	    condp = V3Const::constifyEdit(condp);
	    if (condp->isOne()) {
		// We don't need to add a conditional; we know the existing expression is ok
		condp->deleteTree();
	    }
	    else if (!lvalue
		&& !nodep->backp()->castArraySel()) {	// Too complicated and slow if mid-multidimension
		// ARRAYSEL(...) -> COND(LT(bit<maxbit), ARRAYSEL(...), {width{1'bx}})
		AstNRelinker replaceHandle;
		nodep->unlinkFrBack(&replaceHandle);
		V3Number xnum (nodep->fileline(), nodep->width());
		xnum.setAllBitsX();
		AstNode* newp = new AstCondBound (nodep->fileline(),
						  condp,
						  nodep,
						  new AstConst(nodep->fileline(), xnum));
		if (debug()>=9) newp->dumpTree(cout,"        _new: ");
		// Link in conditional, can blow away temp xor
		replaceHandle.relink(newp);
		// Added X's, tristate them too
		newp->accept(*this);
	    }
	    else if (!lvalue) {  // Mid-multidimension read, just use zero
		// ARRAYSEL(...) -> ARRAYSEL(COND(LT(bit<maxbit), bit, 0))
		AstNRelinker replaceHandle;
		AstNode* bitp = nodep->bitp()->unlinkFrBack(&replaceHandle);
		V3Number zeronum (nodep->fileline(), bitp->width(), 0);
		AstNode* newp = new AstCondBound (bitp->fileline(),
						  condp,
						  bitp,
						  new AstConst(bitp->fileline(), zeronum));
		// Added X's, tristate them too
		if (debug()>=9) newp->dumpTree(cout,"        _new: ");
		replaceHandle.relink(newp);
		newp->accept(*this);
	    }
	    else {  // lvalue
		replaceBoundLvalue(nodep, condp);
	    }
	}
    }