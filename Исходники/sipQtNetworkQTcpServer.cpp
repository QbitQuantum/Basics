static PyObject *meth_QTcpServer_listen(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        const QHostAddress& a0def = QHostAddress::Any;
        const QHostAddress* a0 = &a0def;
        int a0State = 0;
        quint16 a1 = 0;
        QTcpServer *sipCpp;

        static const char *sipKwdList[] = {
            sipName_address,
            sipName_port,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "B|J1t", &sipSelf, sipType_QTcpServer, &sipCpp, sipType_QHostAddress, &a0, &a0State, &a1))
        {
            bool sipRes;

            Py_BEGIN_ALLOW_THREADS
            sipRes = sipCpp->listen(*a0,a1);
            Py_END_ALLOW_THREADS
            sipReleaseType(const_cast<QHostAddress *>(a0),sipType_QHostAddress,a0State);

            return PyBool_FromLong(sipRes);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QTcpServer, sipName_listen, doc_QTcpServer_listen);

    return NULL;
}