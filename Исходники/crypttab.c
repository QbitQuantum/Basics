main()
{
	int i;
	dynatab_t *pt[NTABS];

	for (i=0;i<NTABS;i++) {
		pt[i] = dynatab_create(sizeof(int));
		if (!pt[i]) {
			printf("create: test failed\n");
			exit(1);
		}
		if (dynatab_subscript(pt[i], 1) != NULL) {
			printf("subcript1: test failed\n");
			exit(1);
		}
	}
	for (i=0;i<NTABS;i++) {
		int h;
		h = _heapchk();
		if (h != _HEAPOK) {
			printf("heapchk: test failed\n");
			exit(1);
		}
		test1(pt[i]);
	}
	for (i=0;i<NTABS;i++) 
		dynatab_destroy(pt[i]);
	printf("test okay\n");
	return 0;
}