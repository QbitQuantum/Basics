    virtual void visit(AstParseRef* nodep, AstNUser*) {
	// VarRef: Parse its reference
	UINFO(5,"   "<<nodep<<endl);
	// May be a varref inside a select, etc, so save state and recurse
	string		oldText = m_dotText;
	bool		oldDot = m_inModDot;
	AstParseRefExp  oldExp = m_exp;
	AstText*	oldBasep = m_baseTextp;
	{
	    // Replace the parsed item with its child IE the selection tree down to the varref itself
	    // Do this before iterating, so we don't have to process the edited tree twice
	    AstNode* lhsp = nodep->lhsp()->unlinkFrBack();
	    nodep->replaceWith(lhsp);

	    // Process lower nodes
	    m_dotText = "";
	    m_baseTextp = NULL;
	    if (m_exp == AstParseRefExp::PX_FUNC) {
		lhsp->accept(*this);
		// Return m_dotText to invoker
	    } else if (nodep->expect() == AstParseRefExp::PX_VAR_MEM
		       || nodep->expect() == AstParseRefExp::PX_VAR_ANY) {
		m_exp = nodep->expect();
		lhsp->accept(*this);
		m_exp = AstParseRefExp::PX_NONE;
		if (!m_baseTextp) nodep->v3fatalSrc("No TEXT found to indicate function name");
		if (m_dotText == "") {
		    AstNode* newp = new AstVarRef(nodep->fileline(), m_baseTextp->text(), false);  // lvalue'ness computed later
		    m_baseTextp->replaceWith(newp); m_baseTextp->deleteTree(); m_baseTextp=NULL;
		} else {
		    AstNode* newp = new AstVarXRef(nodep->fileline(), m_baseTextp->text(), m_dotText, false);  // lvalue'ness computed later
		    m_baseTextp->replaceWith(newp); m_baseTextp->deleteTree(); m_baseTextp=NULL;
		}
	    } else {
		nodep->v3fatalSrc("Unknown ParseRefExp type\n");
	    }
	    nodep->deleteTree(); nodep=NULL;
	}
	if (m_exp != AstParseRefExp::PX_FUNC) {  // Fuctions need to look at the name themself
	    m_dotText = oldText;
	    m_inModDot = oldDot;
	    m_exp = oldExp;
	    m_baseTextp = oldBasep;
	}
    }