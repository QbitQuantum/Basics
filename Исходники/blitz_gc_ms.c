static void freeBlock( GCBlock *t ){
	int flags=t->flags;
	int size=flags & ~15;
	int i=size/16;

	if( i>255 ){
		clrMemBit( t );
		heapFree( t,size );
	}else{
		t->flags=BBGC_MARKED;
		t->succ=freeBlocks[i];
		freeBlocks[i]=t;
	}
	gc_alloced-=size;
}