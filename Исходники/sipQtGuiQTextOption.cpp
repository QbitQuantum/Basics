static PyObject *meth_QTextOption_setFlags(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;

    {
        QTextOption::Flags* a0;
        int a0State = 0;
        QTextOption *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ1", &sipSelf, sipType_QTextOption, &sipCpp, sipType_QTextOption_Flags, &a0, &a0State))
        {
            sipCpp->setFlags(*a0);
            sipReleaseType(a0,sipType_QTextOption_Flags,a0State);

            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QTextOption, sipName_setFlags, doc_QTextOption_setFlags);

    return NULL;
}