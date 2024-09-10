void *MA_malloc(unsigned n, void *p) 


{ 
	unsigned sz; 
	int i; 
	Header *h; 
	Header *ph; 
	Header *bh; 
	Header *pbh; 
	unsigned tnb; 
	unsigned nbn; 
	unsigned nbl; 

	if (!CS_init) { 
		INITIALIZECRITICALSECTION(CS); 
		CS_init = 1; 
	} 
	ENTERCRITICALSECTION(CS); 
	if (!n) 
		++n; 
	sz = RND(n); 


	for (i=1 ; Map[i].userBytes && Map[i].userBytes <= sz ; ++i); 
	i--; 



	for (bh=pbh=ph=NULL, h=Map[i].h ; h ; ph=h, h=h->next) 
		if (h->size == sz) { 
		if (ph) 
			ph->next = h->next; 
		else 
			Map[i].h = h->next; 
		h->status = 'U'; 
		h->next = (Header *) p; 
		h->rsize = n; 
		LEAVECRITICALSECTION(CS); 
		return h+1; 
	} else if (h->size > sz && (!bh || bh->size > h->size)) { 
		pbh = ph; 
		bh = h; 
	} 

	if (bh) { 
		if (pbh) 
			pbh->next = bh->next; 
		else 
			Map[i].h = bh->next; 
		bh->status = 'U'; 
		bh->next = (Header *) p; 
		bh->rsize = n; 
		LEAVECRITICALSECTION(CS); 
		return bh+1; 
	} 



	for (i++ ; Map[i].userBytes && !Map[i].h ; ++i); 

	if (!Map[i].userBytes) { 
		more_core(n); 
		LEAVECRITICALSECTION(CS); 
		return MA_malloc(n, p); 
	} 

#line 169 "memalloc.d"
	h = Map[i].h; 
	Map[i].h = h->next; 

	tnb = h->size / sizeof(Header); 
	nbn = sz / sizeof(Header); 
	nbl = tnb - nbn; 
	if (nbl > 5) { 
		bh = h + (nbn + 1); 
		bh->status = 'U'; 
		bh->next = NULL; 
		bh->rsize = bh->size = (nbl - 1) * sizeof(Header); 
		h->size -= nbl * sizeof(Header); 
		MA_free(bh+1); 
	} 
	h->status = 'U'; 
	h->next = (Header *) p; 
	h->rsize = n; 
	LEAVECRITICALSECTION(CS); 
	return h+1; 
} 