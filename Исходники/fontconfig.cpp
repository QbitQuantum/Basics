void init()
{
    Handle<es::Context> root = System()->getRoot();
    framebuffer = root->lookup("device/framebuffer");
    long long size;
    size = framebuffer->getSize();
    framebufferPtr = (u8*) System()->map(0, size,
                                 es::CurrentProcess::PROT_READ | es::CurrentProcess::PROT_WRITE,
                                 es::CurrentProcess::MAP_SHARED,
                                 framebuffer, 0);
}