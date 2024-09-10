LinuxGLContext::LinuxGLContext(const RenderContextDescriptor& desc, Surface& surface, LinuxGLContext* sharedContext) :
    GLContext { sharedContext }
{
    NativeHandle nativeHandle;
    surface.GetNativeHandle(&nativeHandle);
    CreateContext(desc, nativeHandle, sharedContext);
}