/* If only paternity checks were this easy in real life... 
 * Returns 1 if the given 'child' is contained by the 'parent'.*/
int
isancestor(dbref parent, dbref child)
{
	while (child != NOTHING && child != parent) {
		child = getparent(child);
	}
	return child == parent;
}