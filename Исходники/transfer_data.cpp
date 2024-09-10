void
addConstraint( const char *constraint )
{
	if ( global_constraint.Length() > 0 ) {
		global_constraint += " || (";
	} else {
		global_constraint += "(";
	}
	global_constraint += constraint;
	global_constraint += ")";
}