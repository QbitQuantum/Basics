void HashBase::Set(int i, unsigned _hash) {
	if(map) {
		Link& lnk = link[i];
		Unlink(i, lnk);
		int& mi = Maph(_hash & ~UNSIGNED_HIBIT);
		int ii = mi;
		if(ii < 0)
			mi = lnk.prev = lnk.next = i;
		else
		if(i < ii) {
			LinkBefore(i, lnk, ii);
			mi = i;
		}
		else {
			int l = ii;
			int h = link[ii].prev;
			if(h - i < i - l) {
				while(i < h) {
					h = link[h].prev;
				}
				LinkBefore(i, lnk, link[h].next);
			}
			else {
				l = link[l].next;
				while(i > l && l != ii) {
					l = link[l].next;
				}
				LinkBefore(i, lnk, l);
			}
		}
	}
	hash[i] = _hash & ~UNSIGNED_HIBIT;
}