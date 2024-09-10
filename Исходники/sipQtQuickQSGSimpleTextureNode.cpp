static PyObject *meth_QSGSimpleTextureNode_setRect(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;

    {
        const QRectF* a0;
        QSGSimpleTextureNode *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QSGSimpleTextureNode, &sipCpp, sipType_QRectF, &a0))
        {
            sipCpp->setRect(*a0);

            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    {
        qreal a0;
        qreal a1;
        qreal a2;
        qreal a3;
        QSGSimpleTextureNode *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "Bdddd", &sipSelf, sipType_QSGSimpleTextureNode, &sipCpp, &a0, &a1, &a2, &a3))
        {
            sipCpp->setRect(a0,a1,a2,a3);

            Py_INCREF(Py_None);
            return Py_None;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QSGSimpleTextureNode, sipName_setRect, doc_QSGSimpleTextureNode_setRect);

    return NULL;
}