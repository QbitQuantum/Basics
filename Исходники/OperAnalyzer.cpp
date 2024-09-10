    bool OperAnalyzer::analyze(AnalysisVisitor & visitor, ast::Exp & e)
    {
        ast::OpExp & oe = static_cast<ast::OpExp &>(e);
        const ast::OpExp::Oper oper = oe.getOper();
        if (oper == ast::OpExp::plus || oper == ast::OpExp::minus || oper == ast::OpExp::times)
        {
            if (ast::MemfillExp * mfe = analyzeMemfill(visitor, oe))
	    {
		mfe->setVerbose(e.isVerbose());
		e.replace(mfe);

		return true;
	    }
        }

	/*if (ast::ExtendedOpExp * eoe = analyzeMemfill(visitor, oe))
	{
	    eoe->setVerbose(e.isVerbose());
	    e.replace(eoe);
	    
	    return true;
	    }*/
	
	return false;
    }