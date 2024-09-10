bool CEventHandler::UnhookEvent(IUnknown* pSource)
{
#if defined(__USE_ADDBACK_DUAL)
    AtlUnadvise(pSource, __uuidof(IAddBackEvents), cookie_);
#elif defined(__USE_ADDBACK_DISPATCH)
    DispEventUnadvise(pSource, &__uuidof(_IAddBackEvents));
#elif defined(__USE_ADDBACK_BYATTRIB_DISPATCH)
    __unhook(&_IAddBackEvents::ChangedAddEnd, pSource, &CEventHandler::onChangedAddEnd);
    __unhook(&_IAddBackEvents::ChangedSum, pSource, &CEventHandler::onChangedSum);
#endif

    return true;
}