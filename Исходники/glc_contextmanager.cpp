GLC_Context* GLC_ContextManager::currentContext()
{
    QOpenGLContext* pFromContext= QOpenGLContext::currentContext();
    GLC_Context* pSubject= NULL;
    if (NULL != pFromContext)
    {
        if (m_OpenGLContextToGLCContext.contains(pFromContext))
        {
            pSubject= m_OpenGLContextToGLCContext.value(pFromContext);
        }
        else
        {
            pSubject= createContext(pFromContext, pFromContext->surface());
        }
        pSubject->setCurrent();
    }

    return pSubject;
}