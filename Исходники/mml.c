void _serialize(MMLObject* mml, DArray* out, NodeIdx node, uint padding) {
	assert(mml);
	assert(out);

	MMLNode* node_ptr = mml_get_nodeptr(mml, node);
	
	uint i = padding;
	while(i--) {
		darray_append(out, " ");
	}	

	const char* name = mml_get_str(mml, node_ptr->name_start);
	const char* value = mml_get_str(mml, node_ptr->value_start);

	darray_append_multi(out, "( ", 2);
	mml_insert_escapes(name, out);
	darray_append(out, " ");
	mml_insert_escapes(value, out);

	if(node_ptr->first_child_idx == 0) {
		// node has no children, print it on a single line
		darray_append_multi(out, " )\n", 3);
		return;
	}
	else {
		// node has children, recurse
		darray_append(out, "\n");
		NodeIdx child = node_ptr->first_child_idx;
		while(child) {
			_serialize(mml, out, child, padding + 4);
			child = mml_get_next(mml, child);
		}	
		i = padding;
		while(i--) {
			darray_append(out, " ");
		}	
		darray_append_multi(out, ")\n", 2);
	}	
}	