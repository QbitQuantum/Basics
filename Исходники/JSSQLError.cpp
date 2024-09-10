JSValue jsSQLErrorMessage(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSQLError* castedThis = static_cast<JSSQLError*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    SQLError* imp = static_cast<SQLError*>(castedThis->impl());
    JSValue result = jsString(exec, imp->message());
    return result;
}