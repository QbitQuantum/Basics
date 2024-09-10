STDMETHODIMP ProgressWrap::COMGETTER(ErrorInfo)(IVirtualBoxErrorInfo **aErrorInfo)
{
    LogRelFlow(("{%p} %s: enter aErrorInfo=%p\n", this, "Progress::getErrorInfo", aErrorInfo));

    VirtualBoxBase::clearError();

    HRESULT hrc;

    try
    {
        CheckComArgOutPointerValidThrow(aErrorInfo);

        AutoCaller autoCaller(this);
        if (FAILED(autoCaller.rc()))
            throw autoCaller.rc();

        hrc = getErrorInfo(ComTypeOutConverter<IVirtualBoxErrorInfo>(aErrorInfo).ptr());
    }
    catch (HRESULT hrc2)
    {
        hrc = hrc2;
    }
    catch (...)
    {
        hrc = VirtualBoxBase::handleUnexpectedExceptions(this, RT_SRC_POS);
    }

    LogRelFlow(("{%p} %s: leave *aErrorInfo=%p hrc=%Rhrc\n", this, "Progress::getErrorInfo", *aErrorInfo, hrc));
    return hrc;
}