void
DLVertex :: Print ( std::ostream& o ) const
{
	o << "[d(" << getDepth(true) << "/" << getDepth(false)
	  << "),s(" << getSize(true) << "/" << getSize(false)
	  << "),b(" << getBranch(true) << "/" << getBranch(false)
	  << "),g(" << getGener(true) << "/" << getGener(false)
	  << "),f(" << getFreq(true) << "/" << getFreq(false) << ")] ";
	o << getTagName();

	switch ( Type() )
	{
	case dtAnd:		// nothing to do (except for printing operands)
	case dtSplitConcept:
		break;

	case dtTop:		// nothing to do
	case dtNN:
		return;

	case dtDataExpr:
		o << ' ' << *static_cast<const TDataEntry*>(getConcept())->getFacet();
		return;

	case dtDataValue:	// named entry -- just like concept names
	case dtDataType:

	case dtPConcept:
	case dtNConcept:
	case dtPSingleton:
	case dtNSingleton:
		o << '(' << getConcept()->getName() << ") " << (isNNameTag(Type()) ? "=" : "[=") << ' ' << getC();
		return;

	case dtLE:
		o << ' ' << getNumberLE() << ' ' << getRole()->getName() << ' ' << getC();
		return;

	case dtForall:
		o << ' ' << getRole()->getName() << '{' << getState() << '}' << ' ' << getC();
		return;

	case dtIrr:
		o << ' ' << getRole()->getName();
		return;

	case dtProj:
		o << ' ' << getRole()->getName() << ", " << getC() << " => " << getProjRole()->getName();
		return;

	case dtChoose:
		o << ' ' << getC();
		return;

	default:
		std::cerr << "Error printing vertex of type " << getTagName() << "(" << Type() << ")";
		fpp_unreachable();
	}

	// print operands of the concept constructor
	for ( const_iterator q = begin(); q != end(); ++q )
		o << ' ' << *q;
}