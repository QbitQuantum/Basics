static PyObject *rpmfd_fileno(rpmfdObject *s)
{
    int fno;
    if (s->fd == NULL) return err_closed();

    Py_BEGIN_ALLOW_THREADS
    fno = Fileno(s->fd);
    Py_END_ALLOW_THREADS

    if (Ferror(s->fd)) {
	PyErr_SetString(PyExc_IOError, Fstrerror(s->fd));
	return NULL;
    }
    return Py_BuildValue("i", fno);
}