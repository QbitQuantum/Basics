void JSString::visitChildren(JSCell* cell, SlotVisitor& visitor)
{
    JSString* thisObject = jsCast<JSString*>(cell);
    Base::visitChildren(thisObject, visitor);
    
    MARK_LOG_MESSAGE1("[%u]: ", thisObject->length());

#if ENABLE(OBJECT_MARK_LOGGING)
    if (!thisObject->isRope()) {
        WTF::StringImpl* ourImpl = thisObject->m_value.impl();
        if (ourImpl->is8Bit())
            MARK_LOG_MESSAGE1("[8 %p]", ourImpl->characters8());
        else
            MARK_LOG_MESSAGE1("[16 %p]", ourImpl->characters16());
    } else
        MARK_LOG_MESSAGE0("[rope]: ");
#endif

    if (thisObject->isRope())
        static_cast<JSRopeString*>(thisObject)->visitFibers(visitor);
    else {
        StringImpl* impl = thisObject->m_value.impl();
        ASSERT(impl);
        visitor.reportExtraMemoryUsage(impl->costDuringGC());
    }
}