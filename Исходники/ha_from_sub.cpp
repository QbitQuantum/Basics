ParseTree* setDerivedFilter(ParseTree*& n, map<string, ParseTree*>& filterMap, 
                            erydbSelectExecutionPlan::SelectList& derivedTbList)
{
	if (!(n->derivedTable().empty()))
	{
		// @todo replace virtual column of n to real column
		// all simple columns should belong to the same derived table
		erydbSelectExecutionPlan *csep = NULL;
		for (uint i = 0; i < derivedTbList.size(); i++)
		{
			erydbSelectExecutionPlan *plan = dynamic_cast<erydbSelectExecutionPlan*>(derivedTbList[i].get());
			if (plan->derivedTbAlias() == n->derivedTable())
			{
				csep = plan;
				break;
			}
		}
		// should never be null; if null then give up optimization.
		if (!csep)
			return n;

		// 2. push the filter to the derived table filter stack, or 'and' with
		// the filters in the stack
		map<string, ParseTree*>::iterator mapIter = filterMap.find(n->derivedTable());
		if ( mapIter == filterMap.end())
		{
			filterMap.insert(pair<string, ParseTree*>(n->derivedTable(), n));
		}
		else
		{
			ParseTree* pt = new ParseTree(new LogicOperator("and"));
			pt->left(mapIter->second);
			pt->right(n);
			mapIter->second = pt;
		}
		int64_t val = 1;
		n = new ParseTree(new ConstantColumn(val));
	}
	else
	{
		Operator *op = dynamic_cast<Operator*>(n->data());
		if (op && (op->op() == OP_OR || op->op() == OP_XOR))
		{
			return n;
		}
		else
		{
			ParseTree *lhs = n->left();
			ParseTree *rhs = n->right();
			if (lhs)
				n->left(setDerivedFilter(lhs, filterMap, derivedTbList));
			if (rhs)
				n->right(setDerivedFilter(rhs, filterMap, derivedTbList));
		}
	}
	return n;
}