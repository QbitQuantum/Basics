// Collator.find {{{
static PyObject *
icu_Collator_find(icu_Collator *self, PyObject *args, PyObject *kwargs) {
#if PY_VERSION_HEX >= 0x03030000 
#error Not implemented for python >= 3.3
#endif
    PyObject *a_ = NULL, *b_ = NULL;
    UChar *a = NULL, *b = NULL;
    int32_t asz = 0, bsz = 0, pos = -1, length = -1;
    UErrorCode status = U_ZERO_ERROR;
    UStringSearch *search = NULL;
  
    if (!PyArg_ParseTuple(args, "OO", &a_, &b_)) return NULL;

    a = python_to_icu(a_, &asz, 1);
    if (a == NULL) goto end;
    b = python_to_icu(b_, &bsz, 1);
    if (b == NULL) goto end;

    search = usearch_openFromCollator(a, asz, b, bsz, self->collator, NULL, &status);
    if (U_SUCCESS(status)) {
        pos = usearch_first(search, &status);
        if (pos != USEARCH_DONE) {
            length = usearch_getMatchedLength(search);
#ifdef Py_UNICODE_WIDE
            // We have to return number of unicode characters since the string
            // could contain surrogate pairs which are represented as a single
            // character in python wide builds
            length = u_countChar32(b + pos, length);
            pos = u_countChar32(b, pos);
#endif
        } else pos = -1;
    }
end:
    if (search != NULL) usearch_close(search);
    if (a != NULL) free(a);
    if (b != NULL) free(b);

    return (PyErr_Occurred()) ? NULL : Py_BuildValue("ii", pos, length);
} // }}}