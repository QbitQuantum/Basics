PassOwnPtr<AcceleratedCompositingContext> AcceleratedCompositingContext::create(HostWindow* hostWindow)
{
    OwnPtr<AcceleratedCompositingContext> context = adoptPtr(new AcceleratedCompositingContext);
    if (!context->initialize(hostWindow))
        return nullptr;

    return context.release();
}