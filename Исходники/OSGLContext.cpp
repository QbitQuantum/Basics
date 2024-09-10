int
OSGLContext::getMaxOpenGLHeight()
{
    static int maxCPUHeight = 0;
    static int maxGPUHeight = 0;
    if (_imp->useGPUContext) {
        if (maxGPUHeight == 0) {
            boost::shared_ptr<OSGLContextAttacher> attacher;
            if (getCurrentThread() != QThread::currentThread()) {
                attacher = OSGLContextAttacher::create(shared_from_this());
                attacher->attach();
            }
            GL_GPU::GetIntegerv(GL_MAX_TEXTURE_SIZE, &maxGPUHeight);
        }
        return maxGPUHeight;
    } else {
#ifdef HAVE_OSMESA
        if (maxCPUHeight == 0) {
            boost::shared_ptr<OSGLContextAttacher> attacher;
            if (getCurrentThread() != QThread::currentThread()) {
                attacher = OSGLContextAttacher::create(shared_from_this());
                attacher->attach();
            }
            GL_CPU::GetIntegerv(GL_MAX_TEXTURE_SIZE, &maxCPUHeight);
            int osmesaMaxHeight = OSGLContext_osmesa::getMaxHeight();
            maxCPUHeight = std::min(maxCPUHeight, osmesaMaxHeight);
        }
#endif
        return maxCPUHeight;
    }
}