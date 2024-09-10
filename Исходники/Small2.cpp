inline void *MSmall::AllocK(int k)
{
	LOG("AllocK " << (int)k);
	Page *page = work[k]->next;
	for(;;) {
		ASSERT(page->klass == k);
		FreeLink *p = page->freelist;
		if(p) {
			page->freelist = p->next;
			++page->active;
			return p;
		}
		if(page->free > page->Begin()) { // Try swapping with freelist
			void *p = page->free;
			page->free -= page->sz;
			++page->active;
			return p;
		}
		if(page->next != page) {
			page->active = 255;
			page->Unlink();
			page->Link(full[k]);
			page = work[k]->next;
		}
		else {
			page = empty[k]->next;
			if(page->next == page) {
				if(emptypages) {
					emptypages--;
					for(int i = 0; i < 16; i++) { // try inverse direction
						page = empty[i]->next;
						if(page->next != page) {
							page->Unlink();
							break;
						}
					}
					ASSERT(page->next != page);
				}
				else // remote delete should be here!
					page = (Page *)AllocRaw4KB();
				page->Format(k);
				ASSERT(page->klass == k);
			}
			else {
				ASSERT(emptypages > 0);
				page->Unlink();
				emptypages--;
				ASSERT(page->klass == k);
			}
			page->Link(work[k]);
			ASSERT(page->klass == k);
		}
	}
}