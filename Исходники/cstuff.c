static PyObject* cstuff_DirectionMap_fill(cstuff_DirectionMap* self, PyObject *args) {
	PyObject *iterator, *item, *obj;
	int row, col, row2, col2, stride, pos;
	double value, limit;

	queue_s queue = STAILQ_HEAD_INITIALIZER(queue);
	entry_s *entry;

	if (!PyArg_ParseTuple(args, "Od", &obj, &limit)) {
		return NULL;
	}

	iterator = PyObject_GetIter(obj);
	if (iterator == NULL) {
		return NULL;
	}

	while ((item = PyIter_Next(iterator))) {
		if (!PyArg_ParseTuple(item, "ii", &row, &col)) {
			Py_DECREF(item);
			Py_DECREF(iterator);
			cleanup_s(&queue);
			return NULL;
		}
		if (row >= g_rows || col >= g_cols || row < 0 || col < 0) {
			RAISE("Invalid input data - one of the targets is out od map bounds");
			Py_DECREF(iterator);
			cleanup_s(&queue);
			return NULL;
		}
		Py_DECREF(item);
		put_entry_s(row, col, 0.0, row*g_cols+col, &queue, self);
	}
	Py_DECREF(iterator);

	if (PyErr_Occurred()) {
		cleanup_s(&queue);
		return NULL;
	}

	while (!STAILQ_EMPTY(&queue)) {
		entry = STAILQ_FIRST(&queue);
		STAILQ_REMOVE_HEAD(&queue, hook);
		STAILQ_INSERT_TAIL(&free_entries_s, entry, hook);

		row = entry->row;
		col = entry->col;
		value = entry->value;
		stride = row*g_cols;
		value += 1.0;

		if ((limit > 0) && (value > limit)) continue;

		col2 = FMOD((col-1), g_cols);
		pos = stride+col2;
		DO_STUFF(row, col2);

		col2 = FMOD((col+1), g_cols);
		pos = stride+col2;
		DO_STUFF(row, col2);

		row2 = FMOD((row-1), g_rows);
		pos = row2*g_cols+col;
		DO_STUFF(row2, col);

		row2 = FMOD((row+1), g_rows);
		pos = row2*g_cols+col;
		DO_STUFF(row2, col);
	}

	cleanup_s(&queue);
	Py_RETURN_NONE;
}