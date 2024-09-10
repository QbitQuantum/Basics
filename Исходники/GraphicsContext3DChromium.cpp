PassRefPtr<GraphicsContext3D> GraphicsContext3D::create(GraphicsContext3D::Attributes attrs, HostWindow* hostWindow, GraphicsContext3D::RenderStyle renderStyle)
{
    OwnPtr<GraphicsContext3DInternal> internal = adoptPtr(new GraphicsContext3DInternal());
    if (!internal->initialize(attrs, hostWindow, renderStyle == RenderDirectlyToHostWindow)) {
        return 0;
    }
    RefPtr<GraphicsContext3D> result = adoptRef(new GraphicsContext3D(attrs, hostWindow, renderStyle == RenderDirectlyToHostWindow));
    result->m_internal = internal.release();
    return result.release();
}