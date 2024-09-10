void ExpressionTreeUtils::grow(Expression*& top, Operator* op, bool leftside)
{
	bool rightside = !leftside;

	// Can't grow if there is no parent
	if ( !op->parent() )
		return;


	// Can't grow from a side where there is no delimiter
	if ( (leftside && op->descriptor()->prefix().isEmpty() ) || (rightside && op->descriptor()->postfix().isEmpty()) )
		return;

	Operator* parent = op->parent();

	// Get context
	int delim_begin;
	int delim_end;
	op->globalDelimiterBoundaries(leftside ? 0 : op->descriptor()->numOperands(), delim_begin, delim_end);
	ExpressionContext c = top->findContext(leftside ? delim_begin: delim_end);

	// If this is an expression in the middle of two delimiters that belong to the same operator
	// this typically means that it can not be grown any more from only a single side...
	bool wrap_parent = false;
	if (   ( leftside && (c.leftType() == ExpressionContext::None || c.leftType() == ExpressionContext::OpBoundary) )
		 || ( rightside && (c.rightType() == ExpressionContext::None || c.rightType() == ExpressionContext::OpBoundary) )
			 )
	{
		// .. EXCEPT: when both delimiters are the same as the delimiter we're trying to grow and the
		// direction opposite of the growth direction is an end delimiter. In that case we simply
		// engulf the entire parent.
		op->globalDelimiterBoundaries(leftside ? op->descriptor()->numOperands() : 0, delim_begin, delim_end);
		ExpressionContext c_other = top->findContext(leftside ? delim_end : delim_begin );
		if (   ( leftside && c_other.rightType() == ExpressionContext::OpBoundary && c_other.rightText() == op->descriptor()->postfix() && c_other.rightDelim() == c_other.rightOp()->size())
			 || ( rightside && c_other.leftType() == ExpressionContext::OpBoundary && c_other.leftText() == op->descriptor()->prefix() && c_other.leftDelim() == 0) )
			wrap_parent = true;
		else
		return;
	}

	// Special case when the parent ends with a pre/postfix in the direction we're growing.
	// In that case we must wrap the whole operator as we can not break the delimiters.
	wrap_parent = wrap_parent || ( !(leftside && parent->descriptor()->prefix().isEmpty()) && !(rightside && parent->descriptor()->postfix().isEmpty()));
	if (wrap_parent)
	{
		Expression* placeholder = new Empty();
		replace(top, parent, placeholder);
		replace(top, op, leftside ? op->first(true) : op->last(true));
		if (leftside) op->prepend(parent);
		else op->append(parent);
		delete replace(top, placeholder, op);

		return;
	}

	// Find the expression that must be wrapped
	Operator* top_op = parent;
	Operator* child = op;
	while ( (leftside ? top_op->last() : top_op->first()) != child)
	{
		child = top_op;
		top_op = top_op->parent();
		if (!top_op) return;
	}
	Expression* to_wrap = leftside ? top_op->first()->smallestRightmostSubExpr() : top_op->last()->smallestLeftmostSubExpr();

	// Do the exchange --------------------------------------

	// Disconnect top_op from the the entire tree and from it's first and last
	// Note that if we've reached this point then first and last must be two different nodes
	Expression* top_op_placeholder = new Empty();
	replace(top, top_op, top_op_placeholder);
	Expression* top_op_last = top_op->last(true);   // Special case when rightside: top_op_last could be identical to to_wrap
	Expression* top_op_first = top_op->first(true); // Special case when leftside: top_op_first could be identical to to_wrap

	// Disconnect the to_wrap expression if not yet disconnected
	Expression* to_wrap_placeholder = nullptr;
	if ( (leftside && to_wrap != top_op_first) || (rightside && to_wrap != top_op_last) )
	{
		to_wrap_placeholder = new Empty();
		replace(top, to_wrap, to_wrap_placeholder);
	}

	// Disconnect the old_wrapped expression
	Expression* old_wrap = leftside ? op->first(true) : op->last(true); // This is the content that was previously wrapped
	// Disconnect the left and right children of top_op.

	// Make the necessary connections
	if (leftside)
	{
		op->prepend(top_op);
		top_op->prepend(to_wrap);
		top_op->append(old_wrap);
		//Consider the special case
		if (top_op_first == to_wrap)
		{
			delete replace(top, top_op_placeholder, top_op_last );
		}
		else
		{
			delete replace(top, top_op_placeholder, top_op_first );
			delete replace(top, to_wrap_placeholder, top_op_last);
		}
	}
	else
	{
		op->append(top_op);
		top_op->prepend(old_wrap);
		top_op->append(to_wrap);
		//Consider the special case
		if (top_op_last == to_wrap)
		{
			delete replace(top, top_op_placeholder, top_op_first );
		}
		else
		{
			delete replace(top, top_op_placeholder, top_op_last );
			delete replace(top, to_wrap_placeholder, top_op_first);
		}
	}

	fixTop(top);
}