/*************************************************************************
 Routine to return the next entry in the smbdomainalias list.
 *************************************************************************/
BOOL add_domain_alias(LOCAL_GRP **alss, int *num_alss, LOCAL_GRP *als)
{
	if (alss == NULL || num_alss == NULL || als == NULL)
	{
		return False;
	}

	(*alss) = Realloc((*alss), ((*num_alss)+1) * sizeof(LOCAL_GRP));
	if ((*alss) == NULL)
	{
		return False;
	}

	DEBUG(10,("adding alias %s(%s)\n", als->name, als->comment));

	fstrcpy((*alss)[(*num_alss)].name   , als->name);
	fstrcpy((*alss)[(*num_alss)].comment, als->comment);
	(*alss)[(*num_alss)].rid = als->rid;

	(*num_alss)++;

	return True;
}