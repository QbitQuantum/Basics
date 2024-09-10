/**
 * \retval 0 if the entry is unique in the list
 * \retval != if there are several items with this name in the list
 */
static int CheckDuplicateEntry(generic_item * list, const char *name)
{
	generic_item *curr;
	unsigned int found = 0;

	for (curr = list; curr != NULL; curr = curr->next) {
		if ((curr->type == TYPE_BLOCK)
		    && !STRNCMP(curr->item.block.block_name, name, MAXSTRLEN))
			found++;
		if ((curr->type == TYPE_AFFECT)
		    && !STRNCMP(curr->item.affect.varname, name, MAXSTRLEN))
			found++;
		if (found > 1)
			break;
	}
	return (found > 1);
}