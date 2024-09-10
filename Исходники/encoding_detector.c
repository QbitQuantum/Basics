/*
 * Enable or disable the stripping of HTML/XML tags from the input before
 * attempting any detection
 *
 * Returns: Boolean, the value passed
 */
PyObject *
charlockholmes_set_strip_tags(PyObject *self, PyObject *args)
{
    int val;

    if (!PyArg_ParseTuple(args, "i", &val)) {
        return NULL;
    }

	val = val > 0 ? 1 : 0;

	ucsdet_enableInputFilter(ch_ucd, val);

	return PyBool_FromLong(val);
}