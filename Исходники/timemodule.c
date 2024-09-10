static void
PyInit_timezone(PyObject *m) {
    /* This code moved from PyInit_time wholesale to allow calling it from
    time_tzset. In the future, some parts of it can be moved back
    (for platforms that don't HAVE_WORKING_TZSET, when we know what they
    are), and the extraneous calls to tzset(3) should be removed.
    I haven't done this yet, as I don't want to change this code as
    little as possible when introducing the time.tzset and time.tzsetwall
    methods. This should simply be a method of doing the following once,
    at the top of this function and removing the call to tzset() from
    time_tzset():

        #ifdef HAVE_TZSET
        tzset()
        #endif

    And I'm lazy and hate C so nyer.
     */
#if defined(HAVE_TZNAME) && !defined(__GLIBC__) && !defined(__CYGWIN__)
    PyObject *otz0, *otz1;
    tzset();
#ifdef PYOS_OS2
    PyModule_AddIntConstant(m, "timezone", _timezone);
#else /* !PYOS_OS2 */
    PyModule_AddIntConstant(m, "timezone", timezone);
#endif /* PYOS_OS2 */
#ifdef HAVE_ALTZONE
    PyModule_AddIntConstant(m, "altzone", altzone);
#else
#ifdef PYOS_OS2
    PyModule_AddIntConstant(m, "altzone", _timezone-3600);
#else /* !PYOS_OS2 */
    PyModule_AddIntConstant(m, "altzone", timezone-3600);
#endif /* PYOS_OS2 */
#endif
    PyModule_AddIntConstant(m, "daylight", daylight);
    otz0 = PyUnicode_Decode(tzname[0], strlen(tzname[0]), TZNAME_ENCODING, NULL);
    otz1 = PyUnicode_Decode(tzname[1], strlen(tzname[1]), TZNAME_ENCODING, NULL);
    PyModule_AddObject(m, "tzname", Py_BuildValue("(NN)", otz0, otz1));
#else /* !HAVE_TZNAME || __GLIBC__ || __CYGWIN__*/
#ifdef HAVE_STRUCT_TM_TM_ZONE
    {
#define YEAR ((time_t)((365 * 24 + 6) * 3600))
        time_t t;
        struct tm *p;
        long janzone, julyzone;
        char janname[10], julyname[10];
        t = (time((time_t *)0) / YEAR) * YEAR;
        p = localtime(&t);
        janzone = -p->tm_gmtoff;
        strncpy(janname, p->tm_zone ? p->tm_zone : "   ", 9);
        janname[9] = '\0';
        t += YEAR/2;
        p = localtime(&t);
        julyzone = -p->tm_gmtoff;
        strncpy(julyname, p->tm_zone ? p->tm_zone : "   ", 9);
        julyname[9] = '\0';

        if( janzone < julyzone ) {
            /* DST is reversed in the southern hemisphere */
            PyModule_AddIntConstant(m, "timezone", julyzone);
            PyModule_AddIntConstant(m, "altzone", janzone);
            PyModule_AddIntConstant(m, "daylight",
                                    janzone != julyzone);
            PyModule_AddObject(m, "tzname",
                               Py_BuildValue("(zz)",
                                             julyname, janname));
        } else {
            PyModule_AddIntConstant(m, "timezone", janzone);
            PyModule_AddIntConstant(m, "altzone", julyzone);
            PyModule_AddIntConstant(m, "daylight",
                                    janzone != julyzone);
            PyModule_AddObject(m, "tzname",
                               Py_BuildValue("(zz)",
                                             janname, julyname));
        }
    }
#else
#endif /* HAVE_STRUCT_TM_TM_ZONE */
#ifdef __CYGWIN__
    tzset();
    PyModule_AddIntConstant(m, "timezone", _timezone);
    PyModule_AddIntConstant(m, "altzone", _timezone-3600);
    PyModule_AddIntConstant(m, "daylight", _daylight);
    PyModule_AddObject(m, "tzname",
                       Py_BuildValue("(zz)", _tzname[0], _tzname[1]));
#endif /* __CYGWIN__ */
#endif /* !HAVE_TZNAME || __GLIBC__ || __CYGWIN__*/
}