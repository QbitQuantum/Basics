STDMETHODIMP ProcessWrap::COMGETTER(PID)(ULONG *aPID)
{
    LogRelFlow(("{%p} %s: enter aPID=%p\n", this, "Process::getPID", aPID));

    VirtualBoxBase::clearError();

    HRESULT hrc;

    try
    {
        CheckComArgOutPointerValidThrow(aPID);

        AutoCaller autoCaller(this);
        if (FAILED(autoCaller.rc()))
            throw autoCaller.rc();

        hrc = getPID(aPID);
    }
    catch (HRESULT hrc2)
    {
        hrc = hrc2;
    }
    catch (...)
    {
        hrc = VirtualBoxBase::handleUnexpectedExceptions(this, RT_SRC_POS);
    }

    LogRelFlow(("{%p} %s: leave *aPID=%RU32 hrc=%Rhrc\n", this, "Process::getPID", *aPID, hrc));
    return hrc;
}