void addIAL(IntArrayList *a, int i) {
	if (a->count==a->max) {
		//printf("increase max size from %d to %d\n", a->max, a->max+a->increment);
		a->max+=a->increment;

		a->p = ReAlloc(a->p, sizeof(int) * a->max);
		// the same thing
		//int *newp = MAlloc(sizeof(int*) * a->max);
		//memcpy(newp, a->p, sizeof(int*) * a->max);
		//Free(a->p);
		//a->p = newp;

		assert(a->p);
	}
	assertf(a->count < a->max, "count %d max %d", a->count, a->max);
	a->p[a->count++] = i;
}