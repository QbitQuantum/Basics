//*************************************************************************************
//*************************************************************************************
// Removes a linked object Data field from an object
static void EERIE_LINKEDOBJ_Remove(EERIE_3DOBJ * obj, long num)
{
	if (obj == NULL) return;

	if (obj->linked == NULL) return;

	if (num < 0) return;

	if (num >= obj->nblinked) return;

	if (obj->nblinked == 1)
	{
		free(obj->linked);
		obj->linked = NULL;
		obj->nblinked = 0;
		return;
	}

	memcpy(&obj->linked[num], &obj->linked[num+1], sizeof(EERIE_LINKED)*(obj->nblinked - num - 1));
	obj->linked = (EERIE_LINKED *)realloc(obj->linked, sizeof(EERIE_LINKED) * (obj->nblinked - 1));
	obj->nblinked--;
}