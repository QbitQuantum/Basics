static struct commit_list *best_bisection_sorted(struct commit_list *list, int nr)
{
	struct commit_list *p;
	struct commit_dist *array = xcalloc(nr, sizeof(*array));
	int cnt, i;

	for (p = list, cnt = 0; p; p = p->next) {
		int distance;
		unsigned flags = p->item->object.flags;

		if (flags & TREESAME)
			continue;
		distance = weight(p);
		if (nr - distance < distance)
			distance = nr - distance;
		array[cnt].commit = p->item;
		array[cnt].distance = distance;
		cnt++;
	}
	QSORT(array, cnt, compare_commit_dist);
	for (p = list, i = 0; i < cnt; i++) {
		char buf[100]; /* enough for dist=%d */
		struct object *obj = &(array[i].commit->object);

		snprintf(buf, sizeof(buf), "dist=%d", array[i].distance);
		add_name_decoration(DECORATION_NONE, buf, obj);

		p->item = array[i].commit;
		p = p->next;
	}
	if (p)
		p->next = NULL;
	free(array);
	return list;
}