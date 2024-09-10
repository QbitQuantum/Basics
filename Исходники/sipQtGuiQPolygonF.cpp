static int slot_QPolygonF___delitem__(PyObject *sipSelf,PyObject *sipArg)
{
    QPolygonF *sipCpp = reinterpret_cast<QPolygonF *>(sipGetCppPtr((sipSimpleWrapper *)sipSelf,sipType_QPolygonF));

    if (!sipCpp)
        return -1;

    PyObject *sipParseErr = NULL;

    {
        int a0;

        if (sipParseArgs(&sipParseErr, sipArg, "1i", &a0))
        {
            int sipIsErr = 0;

#line 459 "C:\\Users\\marcus\\Downloads\\PyQt-gpl-5.4\\PyQt-gpl-5.4\\sip/QtGui/qpolygon.sip"
int len;

len = sipCpp->count();

if ((a0 = (int)sipConvertFromSequenceIndex(a0, len)) < 0)
    sipIsErr = 1;
else
    sipCpp->remove(a0);
#line 1063 "C:\\Users\\marcus\\Downloads\\PyQt-gpl-5.4\\PyQt-gpl-5.4\\QtGui/sipQtGuiQPolygonF.cpp"

            if (sipIsErr)
                return -1;

            return 0;
        }
    }

    {
        PyObject * a0;

        if (sipParseArgs(&sipParseErr, sipArg, "1T", &PySlice_Type, &a0))
        {
            int sipIsErr = 0;

#line 471 "C:\\Users\\marcus\\Downloads\\PyQt-gpl-5.4\\PyQt-gpl-5.4\\sip/QtGui/qpolygon.sip"
SIP_SSIZE_T len, start, stop, step, slicelength, i;

len = sipCpp->count();

#if PY_VERSION_HEX >= 0x03020000
if (PySlice_GetIndicesEx(a0, len, &start, &stop, &step, &slicelength) < 0)
#else
if (PySlice_GetIndicesEx((PySliceObject *)a0, len, &start, &stop, &step, &slicelength) < 0)
#endif
    sipIsErr = 1;
else
    for (i = 0; i < slicelength; ++i)
    {
        sipCpp->remove(start);
        start += step - 1;
    }
#line 1096 "C:\\Users\\marcus\\Downloads\\PyQt-gpl-5.4\\PyQt-gpl-5.4\\QtGui/sipQtGuiQPolygonF.cpp"

            if (sipIsErr)
                return -1;

            return 0;
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QPolygonF, sipName___delitem__, NULL);

    return -1;
}