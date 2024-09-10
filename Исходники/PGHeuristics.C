//Input: a pair of left/right contexts
//Output: 0,1,2 to apply no rule, rule1, rule2
short ProofGraph::handleRuleApplicationForPredicatePushing(RuleContext& ra1,RuleContext& ra2, const ipartitions_t& mask)
{
	/*	cerr << "Examining (w=" << ra1.getW() << ",v="
			<< ra1.getV() << "," << ra1.getType() <<") and (w="
			<< ra2.getW() << ",v=" << ra2.getV() << "," << ra2.getType() << ")" << endl;*/

	//TODO generalize
	Var pred = pred_to_push;
	bool push_up = false;

	// Swap application rule
	bool(ProofGraph::*allowSwap)(RuleContext& ra,Var v) = &ProofGraph::allowSwapRuleForPredicatePushingDown;
	// Cut application rule
	bool(ProofGraph::*allowCut)(RuleContext& ra,Var v) = &ProofGraph::allowCutRuleForPredicatePushing;


	// Duplication allowed?
	const bool duplAllowedSwap = false;
	const bool duplAllowedCut = false;

	// Check need for duplication
	bool dupl1, dupl2;
	bool allowed1, allowed2;

	short chosen=-1;
	rul_type t1=ra1.getType();
	rul_type t2=ra2.getType();
	bool all1,all2;
	bool is1cut=isCutRule(t1);
	bool is2cut=isCutRule(t2);
	bool is1swap=isSwapRule(t1);
	bool is2swap=isSwapRule(t2);

	//rA1,rA2,rA2u,rA1B,rA2B,rA1undo,rB2k,rB3,rB1,rB2

	//Neither applicable
	if(ra1.disabled() && ra2.disabled())
		chosen=0;
	//First not applicable
	else if(ra1.disabled() && ra2.enabled())
	{
		if( is2cut ) allowed2 =  (*this.*allowCut)(ra2,pred);
		else if( is2swap ) allowed2 = (*this.*allowSwap)(ra2,pred);
		else periplo_error_();
		if(allowed2) chosen=2; else chosen=0;
	}
	//Second not applicable
	else if(ra1.enabled() && ra2.disabled())
	{
		if( is1cut ) allowed1 =  (*this.*allowCut)(ra1,pred);
		else if( is1swap ) allowed1 = (*this.*allowSwap)(ra1,pred);
		else periplo_error_();
		if(allowed1) chosen=1; else chosen=0;
	}
	//Both applicable
	else if(ra1.enabled() && ra2.enabled())
	{
		if( is1cut ) allowed1 =  (*this.*allowCut)(ra1,pred);
		else if( is1swap ) allowed1 = (*this.*allowSwap)(ra1,pred);
		else periplo_error_();

		if( is2cut ) allowed2 =  (*this.*allowCut)(ra2,pred);
		else if( is2swap ) allowed2 = (*this.*allowSwap)(ra2,pred);
		else periplo_error_();

		//Neither allowed
		if(!allowed1 && !allowed2) chosen=0;
		//First allowed
		else if(allowed1 && !allowed2) chosen=1;
		//Second allowed
		else if(!allowed1 && allowed2) chosen=2;
		//Both allowed
		else if(allowed1 && allowed2)
		{
			//Case one cuts, the other swaps: privilege cut
			if(is1cut && is2swap) chosen=1;
			else if(is2cut && is1swap) chosen=2;
			//Case both cut
			else if(is1cut && is2cut)
			{
				//NOTE Privilege the one with the relevant predicate?
				//NOTE probably not necessary
				//Privilege B3 over B1 and B2
				if(t1==rB3 && t2!=rB3) chosen=1;
				else if(t1!=rB3 && t2==rB3) chosen=2;
				//Break ties randomly
				else { if(rand()%2==0) chosen=1; else chosen=2; }
			}
			//Case both swap
			else if(is2swap && is1swap)
			{
				//NOTE Privilege the one with the relevant predicate!
				// v pivot is to be pushed up
				Var	x1, x2;
				if( push_up )
				{
					x1 = getNode(ra1.getV())->getPivot();
					x2 = getNode(ra2.getV())->getPivot();
				}
				// w pivot is to be pushed down
				else
				{
					x1 = getNode(ra1.getW())->getPivot();
					x2 = getNode(ra2.getW())->getPivot();
				}
				if( x1 == pred && x2 != pred ) chosen = 1;
				else if( x1 != pred && x2 == pred ) chosen = 2;
				else
				{
					dupl1=(getNode(ra1.getW())->getNumResolvents() > 1);
					dupl2=(getNode(ra2.getW())->getNumResolvents() > 1);
					//Privilege the one not duplicating
					if(dupl1 && !dupl2) chosen=2;
					else if(!dupl1 && dupl2) chosen=1;
					//Privilege A1undo, then B2k, then A2 over A1
					else if(t1==rA1prime && t2!=rA1prime) chosen=1;
					else if(t1!=rA1prime && t2==rA1prime) chosen=2;
					else if(t1==rB2 && t2!=rB2) chosen=1;
					else if(t1!=rB2 && t2==rB2) chosen=2;
					else if((t1==rA2 || t1==rA2u || t1==rA2B) && (t2==rA1 || t2==rA1B)) chosen=1;
					else if((t2==rA2 || t2==rA2u || t2==rA2B) && (t1==rA1 || t1==rA1B)) chosen=2;
					//Privilege A2B over A2 and A1B over A1
					else if((t1==rA2B && (t2==rA2 || t2==rA2u)) || (t1==rA1B && t2==rA1)) chosen=1;
					else if((t2==rA2B && (t1==rA2 || t1==rA2u)) || (t2==rA1B && t1==rA1)) chosen=2;
					//Break ties randomly
					else{ if(rand()%2==0) chosen=1; else chosen=2; }
				}
			}
		}
	}
	assert(chosen!=-1);
	return chosen;
}