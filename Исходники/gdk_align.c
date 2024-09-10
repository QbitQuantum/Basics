/*
 * Materialize a view into a normal BAT. If it is a slice, we really
 * want to reduce storage of the new BAT.
 */
gdk_return
VIEWreset(BAT *b)
{
	bat hp, tp, hvp, tvp;
	Heap head, tail, hh, th;
	BAT *n = NULL, *v = NULL;

	if (b == NULL)
		return GDK_FAIL;
	hp = VIEWhparent(b);
	tp = VIEWtparent(b);
	hvp = VIEWvhparent(b);
	tvp = VIEWvtparent(b);
	if (hp || tp) {
		BAT *m;
		BATstore *bs;
		BUN cnt;
		str nme;
		size_t nmelen;

		/* alloc heaps */
		memset(&head, 0, sizeof(Heap));
		memset(&tail, 0, sizeof(Heap));
		memset(&hh, 0, sizeof(Heap));
		memset(&th, 0, sizeof(Heap));

		n = BATdescriptor(abs(b->batCacheid)); /* normalized */
		if (n == NULL)
			goto bailout;
		m = BATmirror(n); /* mirror of normalized */
		bs = BBP_desc(n->batCacheid);
		cnt = BATcount(n) + 1;
		nme = BBP_physical(n->batCacheid);
		nmelen = nme ? strlen(nme) : 0;

		assert(n->batCacheid > 0);
		assert(hp || !b->htype);
		assert(tp || !b->ttype);

		head.farmid = BBPselectfarm(n->batRole, n->htype, offheap);
		tail.farmid = BBPselectfarm(n->batRole, n->ttype, offheap);
		if (n->htype) {
			head.filename = (str) GDKmalloc(nmelen + 12);
			if (head.filename == NULL)
				goto bailout;
			snprintf(head.filename, nmelen + 12, "%s.head", nme);
			if (n->htype && HEAPalloc(&head, cnt, Hsize(n)) != GDK_SUCCEED)
				goto bailout;
		}
		if (n->ttype) {
			tail.filename = (str) GDKmalloc(nmelen + 12);
			if (tail.filename == NULL)
				goto bailout;
			snprintf(tail.filename, nmelen + 12, "%s.tail", nme);
			if (n->ttype && HEAPalloc(&tail, cnt, Tsize(n)) != GDK_SUCCEED)
				goto bailout;
		}
		if (n->H->vheap) {
			hh.farmid = BBPselectfarm(n->batRole, n->htype, varheap);
			hh.filename = (str) GDKmalloc(nmelen + 12);
			if (hh.filename == NULL)
				goto bailout;
			snprintf(hh.filename, nmelen + 12, "%s.hheap", nme);
			if (ATOMheap(n->htype, &hh, cnt) != GDK_SUCCEED)
				goto bailout;
		}
		if (n->T->vheap) {
			th.farmid = BBPselectfarm(n->batRole, n->ttype, varheap);
			th.filename = (str) GDKmalloc(nmelen + 12);
			if (th.filename == NULL)
				goto bailout;
			snprintf(th.filename, nmelen + 12, "%s.theap", nme);
			if (ATOMheap(n->ttype, &th, cnt) != GDK_SUCCEED)
				goto bailout;
		}

		v = VIEWcreate(n, n);
		if (v == NULL)
			goto bailout;

		/* cut the link to your parents */
		VIEWunlink(n);
		if (hp) {
			BBPunshare(hp);
			BBPunfix(hp);
		}
		if (tp) {
			BBPunshare(tp);
			BBPunfix(tp);
		}
		if (hvp) {
			BBPunshare(hvp);
			BBPunfix(hvp);
		}
		if (tvp) {
			BBPunshare(tvp);
			BBPunfix(tvp);
		}

		/* make sure everything points there */
		m->S = n->S = &bs->S;
		m->T = n->H = &bs->H;
		m->H = n->T = &bs->T;

		n->H->type = v->H->type;
		n->H->varsized = v->H->varsized;
		n->H->shift = v->H->shift;
		n->H->width = v->H->width;
		n->H->seq = v->H->seq;

		n->T->type = v->T->type;
		n->T->varsized = v->T->varsized;
		n->T->shift = v->T->shift;
		n->T->width = v->T->width;
		n->T->seq = v->T->seq;

		n->H->heap.parentid = n->T->heap.parentid = 0;
		n->batRestricted = BAT_WRITE;

		/* reset BOUND2KEY */
		n->H->key = BAThkey(v);
		n->T->key = BATtkey(v);

		/* copy the heaps */
		n->H->heap = head;
		n->T->heap = tail;

		/* unshare from parents heap */
		if (hh.base) {
			assert(n->H->vheap == NULL);
			n->H->vheap = (Heap *) GDKzalloc(sizeof(Heap));
			if (n->H->vheap == NULL)
				goto bailout;
			*n->H->vheap = hh;
			n->H->vheap->parentid = n->batCacheid;
		}
		if (th.base) {
			assert(n->T->vheap == NULL);
			n->T->vheap = (Heap *) GDKzalloc(sizeof(Heap));
			if (n->T->vheap == NULL)
				goto bailout;
			*n->T->vheap = th;
			n->T->vheap->parentid = n->batCacheid;
		}

		n->batSharecnt = 0;
		n->batCopiedtodisk = 0;
		n->batDirty = 1;

		/* reset BOUND2KEY */
		n->hkey = BAThkey(v);
		n->tkey = BATtkey(v);

		/* make the BAT empty and insert all again */
		DELTAinit(n);
		/* reset capacity */
		n->batCapacity = cnt;

		/* swap n and v in case the original input was reversed, because
		 * BATins demands (v)oid-headed input */
		if (b->batCacheid < 0) {
			n = m;
			m = BATmirror(v);
		} else {
			m = v;
		}
		/* insert all of v in n, and quit */
		BATins(n, m, FALSE);
		BBPreclaim(v);
		BBPunfix(n->batCacheid);
	}
	return GDK_SUCCEED;
      bailout:
	BBPreclaim(v);
	if (n != NULL)
		BBPunfix(n->batCacheid);
	HEAPfree(&head, 0);
	HEAPfree(&tail, 0);
	HEAPfree(&hh, 0);
	HEAPfree(&th, 0);
	return GDK_FAIL;
}