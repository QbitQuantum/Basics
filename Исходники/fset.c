char *get_all_fset(void)
{
	int i;
	char *ret = NULL;
	IrcVariable *ptr;
	FsetNumber *tmp = numeric_fset;
	for (i = 0; i < NUMBER_OF_FSET; i++)
		m_s3cat(&ret, space, fset_array[i].name);
	for (i = 0; i < ext_fset_list.max; i++)
	{
		ptr = ext_fset_list.list[i];
		m_s3cat(&ret, space, ptr->name);
	}
	for (tmp = numeric_fset; tmp; tmp = tmp->next)
		m_s3cat(&ret, space, ltoa(tmp->numeric));
	return ret;
}