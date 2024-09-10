static PyObject *t_localedata_getLocaleSeparator(t_localedata *self)
{
    UChar buffer[256];
    int size;

    STATUS_CALL(size = ulocdata_getLocaleSeparator(self->object, buffer,
                                                   255, &status));

    return PyUnicode_FromUnicodeString(buffer, size);
}