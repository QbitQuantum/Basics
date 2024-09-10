static SQRESULT Thread_exit(HSQUIRRELVM v)
{
    Thread *instance = SQClassType<Thread>::getInstance(v);
    if (instance) {
        return instance->exit(v);
    }
    return ERROR_BADINSTANCE(v);
}