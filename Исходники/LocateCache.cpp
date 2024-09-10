/**
 * Caches the given token sequence in the given cache. Note that
 * match is supposed to contain a single match, not a match list.
 */
static void cache_match_internal(struct match_list* match,const int* tab,int start,int end,LocateCache *c,Abstract_allocator prv_alloc) {
int token=-1;
struct match_list* m=match;
if (start<=end) {
	token=tab[start];
	m=NULL;
}
/* No node */
if (*c==NULL) {
	*c=new_LocateCache(token,m,prv_alloc);
	if (token!=-1) {
		cache_match_internal(match,tab,start+1,end,&((*c)->middle),prv_alloc);
	}
	return;
}
/* There is a node */
if (token<(*c)->token) {
	/* If we have to move on the left */
	return cache_match_internal(match,tab,start,end,&((*c)->left),prv_alloc);
}
if (token>(*c)->token) {
	/* If we have to move on the right */
	return cache_match_internal(match,tab,start,end,&((*c)->right),prv_alloc);
}
/* We have the correct token */
if (token==-1) {
	/* If we are in a final node that already existed, we just add
	 * the new match at the end of the match list to get the same match order as
	 * if the cache system had not been used, but only if the match is not already present */
	struct match_list* *ptr=&((*c)->matches);
	struct match_list* z;
	match->next=NULL;
	while ((*ptr)!=NULL) {
		z=*ptr;
		if (compare_matches(&(z->m),&(match->m))==A_EQUALS_B &&
				!u_strcmp(z->output,match->output)) {
			/* We discard a match that was already in cache */
			free_match_list_element(match,prv_alloc);
			return;
		}
		ptr=&((*ptr)->next);
	}
	(*ptr)=match;
	return;
}
cache_match_internal(match,tab,start+1,end,&((*c)->middle),prv_alloc);
}