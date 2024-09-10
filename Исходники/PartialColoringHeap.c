int heapInsert(PartialColoringHeap *heap, PartialColoring *pc) {
	const int timestep = pc->timestep;

	// create new heaps for new time step
	while (timestep >= heap->alloc_time_count) {
		int newsize = heap->alloc_time_count + heap->time_increment;

		heap->size = ReAlloc(heap->size, newsize*sizeof(int));
		heap->alloc_size = ReAlloc(heap->alloc_size, newsize*sizeof(int));
		heap->arrays = ReAlloc(heap->arrays, newsize*sizeof(PartialColoring**));

		memset(heap->size + heap->alloc_time_count, 0, heap->time_increment*sizeof(int));
		memset(heap->alloc_size + heap->alloc_time_count, 0, heap->time_increment*sizeof(int));
		memset(heap->arrays + heap->alloc_time_count, 0, heap->time_increment*sizeof(PartialColoring **));

		heap->alloc_time_count = newsize;

	}

    //printf("time: item %d heap %d\n", pc->timestep, heap->time_count);

	if (timestep+1>heap->time_count) {
		heap->time_count = timestep+1;
	}

	// increase heap size for new item
	if (heap->size[timestep] >= heap->alloc_size[timestep]) {
		int newsize = heap->alloc_size[timestep] + heap->array_increment;

		heap->arrays[timestep] = ReAlloc(heap->arrays[timestep], newsize * sizeof(PartialColoring*));
		memset(heap->arrays[timestep] + heap->alloc_size[timestep], 0, heap->array_increment*sizeof(PartialColoring **));
		heap->alloc_size[timestep] = newsize;
	}

	heap->arrays[timestep][heap->size[timestep]++] = pc;
	heapifyUp(heap->arrays[timestep], heap->size[timestep]);

	int found=0;
	for (int i=0;i<heap->size[timestep];i++) {
		if (heap->arrays[timestep][i]==pc) { found=1; break; }
	}
	assert(found);

	heap->item_count++;
	assert(heap->item_count>=0);

	return 1;
}