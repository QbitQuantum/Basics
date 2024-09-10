JSValue RegExpConstructor::getBackref(ExecState* exec, unsigned i)
{
    JSArray* array = m_cachedResult.lastResult(exec, this);

    if (i < array->length()) {
        JSValue result = JSValue(array).get(exec, i);
        ASSERT(result.isString() || result.isUndefined());
        if (!result.isUndefined())
            return result;
    }
    return jsEmptyString(exec);
}