bool WCachedParticles::Attempt(const string& filename, int submode, int & error)
{

    JFileSystem* fileSys = JFileSystem::GetInstance();

    if (!fileSys->OpenFile(WResourceManager::Instance()->graphicsFile(filename)))
    {
        error = CACHE_ERROR_404;
        return false;
    }

    SAFE_DELETE(particles);

    particles = NEW hgeParticleSystemInfo;
    // We Skip reading the pointer as it may be larger than 4 bytes in the structure
    void *dummyPointer;
    fileSys->ReadFile(&dummyPointer, 4);
    // we're actually trying to read more than the file size now, but it's no problem.
    // Note that this fix is only to avoid the largest problems, filling a structure
    // by directly reading a file, is really a bad idea ...
    fileSys->ReadFile(&(particles->nEmission), sizeof(hgeParticleSystemInfo) - sizeof(void*));
    fileSys->CloseFile();

    particles->sprite = NULL;
    error = CACHE_ERROR_NONE;
    return true;
}