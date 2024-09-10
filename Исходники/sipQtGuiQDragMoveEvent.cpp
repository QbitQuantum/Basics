static PyObject *meth_QDragMoveEvent_accept(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;

    {
        QDragMoveEvent *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "B", &sipSelf, sipType_QDragMoveEvent, &sipCpp))
        {
            sipCpp->accept();

            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    {
        const QRect* a0;
        QDragMoveEvent *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QDragMoveEvent, &sipCpp, sipType_QRect, &a0))
        {
            sipCpp->accept(*a0);

            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QDragMoveEvent, sipName_accept, doc_QDragMoveEvent_accept);

    return NULL;
}