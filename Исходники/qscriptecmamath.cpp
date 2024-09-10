QScriptValueImpl Math::method_atan2(QScriptContextPrivate *context,
                                    QScriptEnginePrivate *eng,
                                    QScriptClassInfo *)
{
    qsreal v1 = context->argument(0).toNumber();
    qsreal v2 = context->argument(1).toNumber();
#ifdef Q_OS_WINCE
    if (v1 == 0.0) {
        const bool v1MinusZero = _copysign(1.0, v1) < 0.0;
        const bool v2MinusZero = (v2 == 0 && _copysign(1.0, v2) < 0.0);
        if ((v1MinusZero && v2MinusZero) || (v1MinusZero && v2 == -1.0))
            return QScriptValueImpl(eng, -qt_PI);
        if (v2MinusZero)
            return QScriptValueImpl(eng, qt_PI);
        if (v1MinusZero && v2 == 1.0)
            return QScriptValueImpl(eng, -0.0);
#if defined(_X86_)
        if (v2 == 0.0 && (v1MinusZero || (!v1MinusZero && !v2MinusZero)))
            return QScriptValueImpl(eng, 0.0);
#endif
    }
#endif
#if defined(Q_OS_WINCE) && defined(_X86_)
    if (v1 == -1.0 && !_finite(v2) && _copysign(1.0, v2) > 0.0)
        return QScriptValueImpl(eng, -0.0);
#endif
    if ((v1 < 0) && qIsFinite(v1) && qIsInf(v2) && (copySign(1.0, v2) == 1.0))
        return QScriptValueImpl(eng, copySign(0, -1.0));
    if ((v1 == 0.0) && (v2 == 0.0)) {
        if ((copySign(1.0, v1) == 1.0) && (copySign(1.0, v2) == -1.0))
            return QScriptValueImpl(eng, qt_PI);
        else if ((copySign(1.0, v1) == -1.0) && (copySign(1.0, v2) == -1.0))
            return QScriptValueImpl(eng, -qt_PI);
    }
    return (QScriptValueImpl(eng, ::atan2(v1, v2)));
}