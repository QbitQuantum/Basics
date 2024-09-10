static PyObject *py_parse_tree(PyObject *self, PyObject *args)
{
	char *text, *start, *end;
	int len, namelen;
	PyObject *ret, *item, *name;

	if (!PyArg_ParseTuple(args, "s#", &text, &len))
		return NULL;

	/* TODO: currently this returns a list; if memory usage is a concern,
	* consider rewriting as a custom iterator object */
	ret = PyList_New(0);

	if (ret == NULL) {
		return NULL;
	}

	start = text;
	end = text + len;

	while (text < end) {
		long mode;
		mode = strtol(text, &text, 8);

		if (*text != ' ') {
			PyErr_SetString(PyExc_ValueError, "Expected space");
			Py_DECREF(ret);
			return NULL;
		}

		text++;

		namelen = strnlen(text, len - (text - start));

		name = PyString_FromStringAndSize(text, namelen);
		if (name == NULL) {
			Py_DECREF(ret);
			return NULL;
		}

		if (text + namelen + 20 >= end) {
			PyErr_SetString(PyExc_ValueError, "SHA truncated");
			Py_DECREF(ret);
			Py_DECREF(name);
			return NULL;
		}

		item = Py_BuildValue("(NlN)", name, mode,
							 sha_to_pyhex((unsigned char *)text+namelen+1));
		if (item == NULL) {
			Py_DECREF(ret);
			Py_DECREF(name);
			return NULL;
		}
		if (PyList_Append(ret, item) == -1) {
			Py_DECREF(ret);
			Py_DECREF(item);
			return NULL;
		}
		Py_DECREF(item);

		text += namelen+21;
	}

	return ret;
}