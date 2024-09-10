AsmBlock* TGenericBasicType::compileBinaryOperator(NBinaryOperator* binopNode, AsmGenerator& context)
{
	AsmBlock* block = new AsmBlock();

	// get types
	IType* lhsType = binopNode->lhs.getExpressionType(context);
	IType* rhsType = binopNode->rhs.getExpressionType(context);

	// If debugging, clear the values as we POP them.
	if (context.isAssemblerDebug())
	{
		// Put the values into A and B and clear the
		// stack positions as we do so.
		*block <<   *(rhsType->popStackCleanReturn(context, 'B'));
		*block <<   *(lhsType->popStackCleanReturn(context, 'A'));
	}
	else
	{
		// Not debugging, put the values into A and B.
		*block <<   *(rhsType->popStackReturn(context, 'B'));
		*block <<   *(lhsType->popStackReturn(context, 'A'));
	}

	// get promoted type and cast values to result type
	IType* commonType = TGenericBasicType::promoteTypes(lhsType, rhsType);
	if (lhsType != commonType)
	{
		// cast lhsType
		if (lhsType->implicitCastable(context, commonType))
		{
			*block << *(lhsType->implicitCast(context, commonType, 'A'));
		}
		else
		{
			throw new CompilerException(binopNode->line, binopNode->file,
						    "Unable to implicitly cast '" + lhsType->getName()
						    + "' to '" + commonType->getName() + "'");
		}
	}
	else if (rhsType != commonType)
	{
		// cast rhsType
		if (rhsType->implicitCastable(context, commonType))
		{
			*block << *(rhsType->implicitCast(context, commonType, 'B'));
		}
		else
		{
			throw new CompilerException(binopNode->line, binopNode->file,
						    "Unable to implicitly cast '" + rhsType->getName()
						    + "' to '" + commonType->getName() + "'");
		}
	}

	// Now do the appropriate operation.
	switch (binopNode->op)
	{
		case ADD:
			*block << *(commonType->add(context, 'A', 'B'));
			break;

		case SUBTRACT:
			*block << *(commonType->sub(context, 'A', 'B'));
			break;

		case STAR:
			*block << *(commonType->mul(context, 'A', 'B'));
			break;

		case SLASH:
			*block << *(commonType->div(context, 'A', 'B'));
			break;

		case PERCENT:
			*block << *(commonType->mod(context, 'A', 'B'));
			break;

		case BOOLEAN_AND:
			*block << *(commonType->land(context, 'A', 'B'));
			break;

		case BOOLEAN_OR:
			*block << *(commonType->lor(context, 'A', 'B'));
			break;

		case BINARY_AND:
			*block << *(commonType->band(context, 'A', 'B'));
			break;

		case BINARY_OR:
			*block << *(commonType->bor(context, 'A', 'B'));
			break;

		case BINARY_XOR:
			*block << *(commonType->bxor(context, 'A', 'B'));
			break;

		case BINARY_LEFT_SHIFT:
			*block << *(commonType->shl(context, 'A', 'B'));
			break;

		case BINARY_RIGHT_SHIFT:
			*block << *(commonType->shr(context, 'A', 'B'));
			break;

		case COMPARE_EQUAL:
			*block << *(commonType->eq(context, 'A', 'B'));
			break;

		case COMPARE_NOT_EQUAL:
			*block << *(commonType->neq(context, 'A', 'B'));
			break;

		case COMPARE_LESS_THAN:
			*block << *(commonType->lt(context, 'A', 'B'));
			break;

		case COMPARE_LESS_THAN_EQUAL:
			*block << *(commonType->le(context, 'A', 'B'));
			break;

		case COMPARE_GREATER_THAN:
			*block << *(commonType->gt(context, 'A', 'B'));
			break;

		case COMPARE_GREATER_THAN_EQUAL:
			*block << *(commonType->ge(context, 'A', 'B'));
			break;

		default:
			throw new CompilerException(binopNode->line, binopNode->file, "Unknown binary operations requested.");
	}

	return block;
}