ngx_http_whitelist_rule_t *
ngx_http_wlr_find(ngx_conf_t *cf, ngx_http_dummy_loc_conf_t *dlc,
		  ngx_http_rule_t *curr, int zone, int uri_idx,
		  int name_idx, char **fullname) {
  uint i;
  
  /* Create unique string for rule, and try to find it in existing rules.*/
  /*name AND uri*/
  
  if (uri_idx != -1 && name_idx != -1) {
#ifdef whitelist_heavy_debug
    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, 
		       "whitelist has uri + name");
#endif
    /* allocate one extra byte in case curr->br->target_name is set. */
    *fullname = ngx_pcalloc(cf->pool, custloc_array(curr->br->custom_locations->elts)[name_idx].target.len +
			    custloc_array(curr->br->custom_locations->elts)[uri_idx].target.len + 3);
    /* if WL targets variable name instead of content, prefix hash with '#' */
    if (curr->br->target_name)
      strncat(*fullname, (const char *) "#", 1);
    strncat(*fullname, (const char *) custloc_array(curr->br->custom_locations->elts)[uri_idx].target.data, 
	    custloc_array(curr->br->custom_locations->elts)[uri_idx].target.len);
    strncat(*fullname, (const char *) "#", 1);
    strncat(*fullname, (const char *) custloc_array(curr->br->custom_locations->elts)[name_idx].target.data, 
	    custloc_array(curr->br->custom_locations->elts)[name_idx].target.len);
  }
  /* only uri */
  else if (uri_idx != -1 && name_idx == -1) {
#ifdef whitelist_heavy_debug
    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, 
		       "whitelist has uri");
#endif
    //XXX set flag only_uri
    *fullname = ngx_pcalloc(cf->pool, custloc_array(curr->br->custom_locations->elts)[uri_idx].target.len + 1);
    strncat(*fullname, (const char *) custloc_array(curr->br->custom_locations->elts)[uri_idx].target.data, 
	    custloc_array(curr->br->custom_locations->elts)[uri_idx].target.len);
  }
  /* only name */
  else if (name_idx != -1) {
#ifdef whitelist_heavy_debug
    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, 
		       "whitelist has name");
#endif
    *fullname = ngx_pcalloc(cf->pool, custloc_array(curr->br->custom_locations->elts)[name_idx].target.len + 2);
    if (curr->br->target_name)
      strncat(*fullname, (const char *) "#", 1);
    strncat(*fullname, (const char *) custloc_array(curr->br->custom_locations->elts)[name_idx].target.data, 
	    custloc_array(curr->br->custom_locations->elts)[name_idx].target.len);
  }
  /* problem houston */
  else
    return (NULL);
  
  for (i = 0; i < dlc->tmp_wlr->nelts; i++)
    if (!strcmp((const char *)*fullname, (const char *)((ngx_http_whitelist_rule_t *) dlc->tmp_wlr->elts)[i].name->data) && 
	((ngx_http_whitelist_rule_t *) dlc->tmp_wlr->elts)[i].zone == (uint) zone)
      {
#ifdef whitelist_heavy_debug
	ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, 
			   "found existing 'same' WL : %V", ((ngx_http_whitelist_rule_t *) dlc->tmp_wlr->elts)[i].name);
#endif
	return (&((ngx_http_whitelist_rule_t *)dlc->tmp_wlr->elts)[i]);
      }
  return (NULL);
}