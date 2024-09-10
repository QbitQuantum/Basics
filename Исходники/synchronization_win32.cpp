Error Cond::create(Cond **returnValue)
{
    Cond *cond = new Cond;
    InitializeConditionVariable(&cond->mNativeCond);
    *returnValue = cond;
    return Error(0);
}