	~PyADS_ATTR_INFO() {
		InvalidateName();
		InvalidateValues();
		Py_XDECREF(obName);
		Py_XDECREF(obValues);
	}