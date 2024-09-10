static PyObject *meth_QGestureEvent_accept(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;

    {
        QGestureEvent *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "B", &sipSelf, sipType_QGestureEvent, &sipCpp))
        {
            sipCpp->accept();

            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    {
        QGesture* a0;
        QGestureEvent *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ8", &sipSelf, sipType_QGestureEvent, &sipCpp, sipType_QGesture, &a0))
        {
            sipCpp->accept(a0);

            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    {
        Qt::GestureType a0;
        QGestureEvent *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BE", &sipSelf, sipType_QGestureEvent, &sipCpp, sipType_Qt_GestureType, &a0))
        {
            sipCpp->accept(a0);

            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QGestureEvent, sipName_accept, doc_QGestureEvent_accept);

    return NULL;
}