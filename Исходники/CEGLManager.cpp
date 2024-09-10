CEGLManager::~CEGLManager()
{
    destroyContext();
    destroySurface();
    terminate();
}