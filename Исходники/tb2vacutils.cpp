bool VACVariable::averaging()
{
	Cost Top = wcsp->getUb();
	bool change = false;
	EnumeratedVariable* x;
	EnumeratedVariable* y;
	Constraint* ctr = NULL;
	ConstraintList::iterator itc = getConstrs()->begin();
	if(itc != getConstrs()->end())	ctr = (*itc).constr;
	while(ctr) {
		if(ctr->arity() == 2 && !ctr->isSep()) {
			BinaryConstraint* bctr = (BinaryConstraint*) ctr;
			x = (EnumeratedVariable*) bctr->getVarDiffFrom( (Variable*) this );
			for (iterator it = begin(); it != end(); ++it) {
				Cost cu = getCost(*it);
				Cost cmin = Top;
				for (iterator itx = x->begin(); itx != x->end(); ++itx) {
					Cost cbin = bctr->getCost(this,x,*it,*itx);
					if(cbin < cmin) cmin = cbin;
				}
				assert(cmin < Top);
				Double mean = to_double(cmin + cu) / 2.;	
				Double extc = to_double(cu) - mean;					 
				if(abs(extc) >= 1) {
				  Cost costi = (Long) extc;
				  for (iterator itx = x->begin(); itx != x->end(); ++itx) {
					bctr->addcost(this,x,*it,*itx,costi);				
				  }
				  if(mean > to_double(cu)) project(*it, -costi); 
				  else extend(*it, costi);
				  change = true;
				}
			}
		} else if(ctr->arity() == 3 && !ctr->isSep()) {
			TernaryConstraint* tctr = (TernaryConstraint*) ctr;
			x = (EnumeratedVariable*) tctr->getVar( 0 );
			if(x == this) x = (EnumeratedVariable*) tctr->getVar( 1 );
		    y = (EnumeratedVariable*) tctr->getVarDiffFrom((Variable*) this, (Variable*)x);
			for (iterator it = begin(); it != end(); ++it) {
				Cost cu = getCost(*it);
				Cost cmin = Top;
				for (iterator itx = x->begin(); itx != x->end(); ++itx) {
				for (iterator ity = y->begin(); ity != y->end(); ++ity) {
					Cost ctern = tctr->getCost(this,x,y,*it,*itx,*ity);
					if(ctern < cmin) cmin = ctern;
				}}
				assert(cmin < Top);
				Double mean = to_double(cmin + cu) / 2.;
				Double extc = to_double(cu) - mean;				 
				if(abs(extc) >= 1) {
					Cost costi = (Long) extc;
					for (iterator itx = x->begin(); itx != x->end(); ++itx) {
					for (iterator ity = y->begin(); ity != y->end(); ++ity) {
						tctr->addCost(this,x,y,*it,*itx,*ity,costi);				
					}}
					if(mean > to_double(cu)) project(*it, -costi); 
					else extend(*it, costi);
					change = true;
				}
			}
		} else if(ctr->arity() >= 4 && ctr->extension() && !ctr->isSep()) {
			NaryConstraint* nctr = (NaryConstraint*) ctr;
			for (iterator it = begin(); it != end(); ++it) {
				Cost cu = getCost(*it);
				Cost cmin = Top;
				int tindex = nctr->getIndex(this);
				String tuple;
				Cost cost;
				Long nbtuples = 0;
				nctr->first();
				while (nctr->next(tuple,cost)) {
				  nbtuples++;
				  if (toValue(tuple[tindex] - CHAR_FIRST)==(*it) && cost < cmin) cmin = cost;
				}
				if (nctr->getDefCost() < cmin && nbtuples < nctr->getDomainSizeProduct()) cmin = nctr->getDefCost();
				//				assert(cmin < Top);
				Double mean = to_double(cmin + cu) / 2.;
				Double extc = to_double(cu) - mean;				 
				if(abs(extc) >= 1) {
					Cost costi = (Cost) extc;
					if(nctr->getDefCost() < Top) {
					  nctr->firstlex();
					  while( nctr->nextlex(tuple,cost) ) {
						if (toValue(tuple[tindex] - CHAR_FIRST)==(*it)) {
						  if(cost + costi < Top) nctr->setTuple(tuple, cost + costi);
						  else nctr->setTuple(tuple, Top);
						}
					  }
					  nctr->setDefCost(Top);
					} else {
					  nctr->first();
					  while( nctr->next(tuple,cost) ) {
						if (toValue(tuple[tindex] - CHAR_FIRST)==(*it)) {
						  if(cost + costi < Top) nctr->addtoTuple(tuple, costi);
						  else nctr->setTuple(tuple, Top);
						}
					  }
					}
					if(mean > to_double(cu)) project(*it, -costi); 
					else extend(*it, costi);
					change = true;
				}
			}
		}
		++itc;
		if(itc != getConstrs()->end()) ctr = (*itc).constr;
		else ctr = NULL;
	}
	return change;
}