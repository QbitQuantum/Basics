/**
 * Add a generic link (input or output) to a container
 */
mjrlink_t	*mjr_container_add_link(mjrcontext_t	*ctx,
					container_t	*cntnr,
					unsigned int	id,
					u_char		link_type,
					u_char		link_scope,
					int		link_direction)
{
  list_t	*linklist;
  listent_t	*listent;
  listent_t	*savednext;
  mjrlink_t	*link;
  container_t	*cnt;
  char		linkname[BUFSIZ];

  PROFILER_IN(__FILE__, __FUNCTION__, __LINE__);

#if __DEBUG_CNTNR__
  if (cntnr->id == id)
    fprintf(D_DESC, "[D] %s: linking the same container id:%d\n",
	    __FUNCTION__, id);
#endif

  /* Check if we are linked with container id by other link type */
  linklist = mjr_link_get_by_direction(cntnr, link_direction);
  for (listent = linklist->head; listent; listent = savednext)
    {
      link      = (mjrlink_t *) listent->data;
      cnt       = ctx->reg_containers[link->id];
      savednext = listent->next;

      if (cnt->type == cntnr->type && link->id == id)
	{

#if __DEBUG_CNTNR__
	  fprintf(D_DESC, "[D] %s: already linked with id:%d type:%d/%d\n",
		  __FUNCTION__, id, link->type, link_type);
#endif

	  if (link->type == link_type)
	    {

#if __DEBUG_CNTNR__
	      fprintf(D_DESC,"[D] %s: return existing link id:%d\n", __FUNCTION__, id);
#endif

	      PROFILER_ROUT(__FILE__, __FUNCTION__, __LINE__, link);
	    }

	  else if ((link->type == MJR_LINK_BLOCK_COND_ALWAYS) &&
		   ((link_type == MJR_LINK_BLOCK_COND_TRUE) ||
		    (link_type == MJR_LINK_BLOCK_COND_FALSE)))
	    {

#if __DEBUG_CNTNR__
	      fprintf(D_DESC,"[D] %s: removing old unconditional link id:%d for condlink type %d\n",
		      __FUNCTION__, id, link_type);
#endif

	      elist_del(linklist, listent->key);
	    }
	}
    }

#if __DEBUG_CNTNR__
  fprintf(D_DESC,"[D] %s: link id:%d -> id:%d type:%d dir:%d\n",
	  __FUNCTION__, cntnr->id, id, link_type, link_direction);
#endif

  /* Create and add the new link */
  XALLOC(__FILE__, __FUNCTION__, __LINE__, link, sizeof(mjrlink_t), NULL);
  link->id   = id;
  link->type = link_type;
  link->scope = link_scope;
  snprintf(linkname, sizeof(linkname), "%u_%u", cntnr->id, id);
  elist_add(linklist, strdup(linkname), link);
  hash_add(&ctx->linkhash, strdup(linkname), link);
  PROFILER_ROUT(__FILE__, __FUNCTION__, __LINE__, link);
}