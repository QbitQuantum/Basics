// Generate unique AtomType name with base name provided
const char* DUQ::uniqueAtomTypeName(const char* base, AtomType* exclude) const
{
	static Dnchar uniqueName;
	Dnchar baseName = base;
	AtomType* at;
	int highest = -1;
	
	if (baseName.isEmpty()) baseName = "Unnamed";

	// Find all existing names which are the same as 'baseName' up to the first '_', and get the highest appended number
	for (at = atomTypes_.first(); at != NULL; at = at->next)
	{
		if ( at == exclude) continue;
		if (strcmp(baseName, at->name()) == 0) highest = 0;
		else if (strcmp(baseName,DUQSys::beforeLastChar(at->name(),'_')) == 0) highest = atoi(DUQSys::afterLastChar(at->name(), '_'));
	}
	if (highest > -1) uniqueName.sprintf("%s_%i", baseName.get(), ++highest);
	else uniqueName = baseName;
	
	return uniqueName;
}