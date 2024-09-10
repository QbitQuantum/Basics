eit_ext_desc_t* epg_get_ext_desc(eit_event_info_t *ep)
{
	eit_ext_desc_t *p;

	if (ep == NULL)
		return NULL;

	p = ep->eit_ext_desc;
	if(p == NULL)
		return NULL;

	while(p != NULL)
	{
		if(MEMCMP(p->lang_code, g_current_lang_code, 3) == 0)
			break;
		p = p->next;
	}
	if(p==NULL)
		p = ep->eit_ext_desc;
	return p;

}