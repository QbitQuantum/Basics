void resolve_tree_islands(struct repository *r,
			  int progress,
			  struct packing_data *to_pack)
{
	struct progress *progress_state = NULL;
	struct tree_islands_todo *todo;
	int nr = 0;
	int i;

	if (!island_marks)
		return;

	/*
	 * We process only trees, as commits and tags have already been handled
	 * (and passed their marks on to root trees, as well. We must make sure
	 * to process them in descending tree-depth order so that marks
	 * propagate down the tree properly, even if a sub-tree is found in
	 * multiple parent trees.
	 */
	ALLOC_ARRAY(todo, to_pack->nr_objects);
	for (i = 0; i < to_pack->nr_objects; i++) {
		if (oe_type(&to_pack->objects[i]) == OBJ_TREE) {
			todo[nr].entry = &to_pack->objects[i];
			todo[nr].depth = oe_tree_depth(to_pack, &to_pack->objects[i]);
			nr++;
		}
	}
	QSORT(todo, nr, tree_depth_compare);

	if (progress)
		progress_state = start_progress(_("Propagating island marks"), nr);

	for (i = 0; i < nr; i++) {
		struct object_entry *ent = todo[i].entry;
		struct island_bitmap *root_marks;
		struct tree *tree;
		struct tree_desc desc;
		struct name_entry entry;
		khiter_t pos;

		pos = kh_get_sha1(island_marks, ent->idx.oid.hash);
		if (pos >= kh_end(island_marks))
			continue;

		root_marks = kh_value(island_marks, pos);

		tree = lookup_tree(r, &ent->idx.oid);
		if (!tree || parse_tree(tree) < 0)
			die(_("bad tree object %s"), oid_to_hex(&ent->idx.oid));

		init_tree_desc(&desc, tree->buffer, tree->size);
		while (tree_entry(&desc, &entry)) {
			struct object *obj;

			if (S_ISGITLINK(entry.mode))
				continue;

			obj = lookup_object(r, entry.oid->hash);
			if (!obj)
				continue;

			set_island_marks(obj, root_marks);
		}

		free_tree_buffer(tree);

		display_progress(progress_state, i+1);
	}

	stop_progress(&progress_state);
	free(todo);
}