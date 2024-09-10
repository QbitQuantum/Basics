AST::Ptr SimplifyRoot(AST::Ptr ast, Address addr) {
    if (ast->getID() == AST::V_RoseAST) {
        RoseAST::Ptr roseAST = boost::static_pointer_cast<RoseAST>(ast); 
	
	switch (roseAST->val().op) {
	    case ROSEOperation::invertOp:
	        if (roseAST->child(0)->getID() == AST::V_RoseAST) {
		    RoseAST::Ptr child = boost::static_pointer_cast<RoseAST>(roseAST->child(0));
		    if (child->val().op == ROSEOperation::invertOp) return child->child(0);
		} else if (roseAST->child(0)->getID() == AST::V_ConstantAST) {
		    ConstantAST::Ptr child = boost::static_pointer_cast<ConstantAST>(roseAST->child(0));
		    size_t size = child->val().size;
		    uint64_t val = child->val().val;
		    if (size < 64) {
		        uint64_t mask = (1ULL << size) - 1;
		        val = (~val) & mask;
		    } else
		        val = ~val;
		    return ConstantAST::create(Constant(val, size));
		}
		break;
	    case ROSEOperation::extendMSBOp:
	    case ROSEOperation::extractOp:
	    case ROSEOperation::signExtendOp:
	    case ROSEOperation::concatOp:
	        return roseAST->child(0);

	    case ROSEOperation::addOp:
	        // We simplify the addition as much as we can
		// Case 1: two constants
	        if (roseAST->child(0)->getID() == AST::V_ConstantAST && roseAST->child(1)->getID() == AST::V_ConstantAST) {
		    ConstantAST::Ptr child0 = boost::static_pointer_cast<ConstantAST>(roseAST->child(0));
		    ConstantAST::Ptr child1 = boost::static_pointer_cast<ConstantAST>(roseAST->child(1));
		    uint64_t val = child0->val().val + child1->val().val;
		    size_t size;
		    if (child0->val().size > child1->val().size)
		        size = child0->val().size;
		    else
		        size = child1->val().size;
		    return ConstantAST::create(Constant(val,size));
   	        }
		// Case 2: anything adding zero stays the same
		if (roseAST->child(0)->getID() == AST::V_ConstantAST) {
		    ConstantAST::Ptr child = boost::static_pointer_cast<ConstantAST>(roseAST->child(0));
		    if (child->val().val == 0) return roseAST->child(1);
		}
		if (roseAST->child(1)->getID() == AST::V_ConstantAST) {
		    ConstantAST::Ptr child = boost::static_pointer_cast<ConstantAST>(roseAST->child(1));
		    if (child->val().val == 0) return roseAST->child(0);
		}
		// Case 3: if v + v * c = v * (c+1), where v is a variable and c is a constant
		if (roseAST->child(0)->getID() == AST::V_VariableAST && roseAST->child(1)->getID() == AST::V_RoseAST) {
		    RoseAST::Ptr rOp = boost::static_pointer_cast<RoseAST>(roseAST->child(1));
		    if (rOp->val().op == ROSEOperation::uMultOp || rOp->val().op == ROSEOperation::sMultOp) {
		        if (rOp->child(0)->getID() == AST::V_VariableAST && rOp->child(1)->getID() == AST::V_ConstantAST) {
			    VariableAST::Ptr varAST1 = boost::static_pointer_cast<VariableAST>(roseAST->child(0));
			    VariableAST::Ptr varAST2 = boost::static_pointer_cast<VariableAST>(rOp->child(0));
			    if (varAST1->val().reg == varAST2->val().reg) {
			        ConstantAST::Ptr oldC = boost::static_pointer_cast<ConstantAST>(rOp->child(1));
			        ConstantAST::Ptr newC = ConstantAST::create(Constant(oldC->val().val + 1, oldC->val().size));
				RoseAST::Ptr newRoot = RoseAST::create(ROSEOperation(rOp->val()), varAST1, newC);
				return newRoot;
			    }
			}
		    }
		} 
		break;
	    case ROSEOperation::sMultOp:
	    case ROSEOperation::uMultOp:
	        if (roseAST->child(0)->getID() == AST::V_ConstantAST) {
		    ConstantAST::Ptr child0 = boost::static_pointer_cast<ConstantAST>(roseAST->child(0));
		    if (child0->val().val == 1) return roseAST->child(1);
		}

	        if (roseAST->child(1)->getID() == AST::V_ConstantAST) {
		    ConstantAST::Ptr child1 = boost::static_pointer_cast<ConstantAST>(roseAST->child(1));
		    if (child1->val().val == 1) return roseAST->child(0);
		}
	        break;

	    case ROSEOperation::xorOp:
	        if (roseAST->child(0)->getID() == AST::V_VariableAST && roseAST->child(1)->getID() == AST::V_VariableAST) {
		    VariableAST::Ptr child0 = boost::static_pointer_cast<VariableAST>(roseAST->child(0)); 
		    VariableAST::Ptr child1 = boost::static_pointer_cast<VariableAST>(roseAST->child(1)); 
		    if (child0->val() == child1->val()) {
		        return ConstantAST::create(Constant(0 , 32));
		    }
  	        }
		break;
	    case ROSEOperation::derefOp:
	        // Any 8-bit value is bounded in [0,255].
		// Need to keep the length of the dereference if it is 8-bit.
		// However, dereference longer than 8-bit should be regarded the same.
	        if (roseAST->val().size == 8)
		    return ast;
		else
		    return RoseAST::create(ROSEOperation(ROSEOperation::derefOp), ast->child(0));
		break;
	    case ROSEOperation::shiftLOp:
	        if (roseAST->child(0)->getID() == AST::V_ConstantAST && roseAST->child(1)->getID() == AST::V_ConstantAST) {
		    ConstantAST::Ptr child0 = boost::static_pointer_cast<ConstantAST>(roseAST->child(0));
		    ConstantAST::Ptr child1 = boost::static_pointer_cast<ConstantAST>(roseAST->child(1));
		    return ConstantAST::create(Constant(child0->val().val << child1->val().val, 64));
		}
		break;
	    case ROSEOperation::andOp:
	        if (roseAST->child(0)->getID() == AST::V_ConstantAST && roseAST->child(1)->getID() == AST::V_ConstantAST) {
		    ConstantAST::Ptr child0 = boost::static_pointer_cast<ConstantAST>(roseAST->child(0));
		    ConstantAST::Ptr child1 = boost::static_pointer_cast<ConstantAST>(roseAST->child(1));
		    return ConstantAST::create(Constant(child0->val().val & child1->val().val, 64));
		}
		break;
	    case ROSEOperation::orOp:
	        if (roseAST->child(0)->getID() == AST::V_ConstantAST && roseAST->child(1)->getID() == AST::V_ConstantAST) {
		    ConstantAST::Ptr child0 = boost::static_pointer_cast<ConstantAST>(roseAST->child(0));
		    ConstantAST::Ptr child1 = boost::static_pointer_cast<ConstantAST>(roseAST->child(1));
		    return ConstantAST::create(Constant(child0->val().val | child1->val().val, 64));
		}
		break;

	    default:
	        break;

	}
    } else if (ast->getID() == AST::V_VariableAST) {
        VariableAST::Ptr varAST = boost::static_pointer_cast<VariableAST>(ast);
	if (varAST->val().reg.absloc().isPC()) {
	    MachRegister pc = varAST->val().reg.absloc().reg();	    
	    return ConstantAST::create(Constant(addr, getArchAddressWidth(pc.getArchitecture()) * 8));
	}
	// We do not care about the address of the a-loc
	// because we will keep tracking the changes of 
	// each a-loc. Also, this brings a benefit that
	// we can directly use ast->isStrictEqual() to 
	// compare two ast.
	return VariableAST::create(Variable(varAST->val().reg));
    } else if (ast->getID() == AST::V_ConstantAST) {
        ConstantAST::Ptr constAST = boost::static_pointer_cast<ConstantAST>(ast);
	size_t size = constAST->val().size;
	uint64_t val = constAST->val().val;	
	if (size == 32)
	    if (!(val & (1ULL << (size - 1))))
	        return ConstantAST::create(Constant(val, 64));
    }

    return ast;
}