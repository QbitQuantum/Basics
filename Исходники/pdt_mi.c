struct mi_root* pdt_mi_list(struct mi_root* cmd_tree, void* param)
{
	str sd, sp, sdomain;
	pdt_tree_t *pt;
	struct mi_node* node = NULL;
	unsigned int i= 0;
	struct mi_root* rpl_tree = NULL;
	struct mi_node* rpl = NULL;
	static char code_buf[PDT_MAX_DEPTH+1];
	int len;
	str *cl;
	pdt_tree_t **ptree;

	ptree = pdt_get_ptree();

	if(ptree==NULL)
	{
		LM_ERR("empty domain list\n");
		return init_mi_tree( 500, MI_INTERNAL_ERR_S, MI_INTERNAL_ERR_LEN);
	}

	cl = pdt_get_char_list();

	/* read sdomain */
	sdomain.s = 0;
	sdomain.len = 0;
	sp.s = 0;
	sp.len = 0;
	sd.s = 0;
	sd.len = 0;
	node = cmd_tree->node.kids;
	if(node != NULL)
	{
		sdomain = node->value;
		if(sdomain.s == NULL || sdomain.len== 0)
			return init_mi_tree( 404, "domain not found", 16);

		if(*sdomain.s=='.')
			sdomain.s = 0;

		/* read prefix */
		node = node->next;
		if(node != NULL)
		{
			sp= node->value;
			if(sp.s== NULL || sp.len==0 || *sp.s=='.')
				sp.s = NULL;
			else {
				while(sp.s!=NULL && i!=sp.len)
				{
					if(strpos(cl->s, sp.s[i]) < 0)
					{
						LM_ERR("bad prefix [%.*s]\n", sp.len, sp.s);
						return init_mi_tree( 400, "bad prefix", 10);
					}
					i++;
				}
			}

			/* read domain */
			node= node->next;
			if(node != NULL)
			{
				sd= node->value;
				if(sd.s== NULL || sd.len==0 || *sd.s=='.')
					sd.s = NULL;
			}
		}
	}

	rpl_tree = init_mi_tree(200, MI_OK_S, MI_OK_LEN);
	if(rpl_tree == NULL)
		return 0;
	rpl = &rpl_tree->node;

	if(*ptree==0)
		return rpl_tree;

	pt = *ptree;
	
	while(pt!=NULL)
	{
		if(sdomain.s==NULL || 
			(sdomain.s!=NULL && pt->sdomain.len>=sdomain.len && 
			 strncmp(pt->sdomain.s, sdomain.s, sdomain.len)==0))
		{
			len = 0;
			if(pdt_print_mi_node(pt->head, rpl, code_buf, len, &pt->sdomain,
						&sd, &sp)<0)
				goto error;
		}
		pt = pt->next;
	}
	
	return rpl_tree;

error:
	free_mi_tree(rpl_tree);
	return 0;
}