static PyObject *
ICUConverter_getICUVersion(ICUConverter *self, PyObject *args)
{
	assert(self != NULL);

	if (! PyArg_ParseTuple(args, "")) {
		return NULL;
	}

	if (self->pDecoder != NULL) {
		// typedef uint8_t UVersionInfo[U_MAX_VERSION_LENGTH];
		uint8_t versionInfo[U_MAX_VERSION_LENGTH];
		BOOST_STATIC_ASSERT(U_MAX_VERSION_LENGTH == 4);

		u_getVersion(versionInfo);
		return Py_BuildValue("iiii", (int)versionInfo[0], (int)versionInfo[1], (int)versionInfo[2], (int)versionInfo[3]);
	}

	// return None
    Py_INCREF(Py_None);
    return Py_None;
}