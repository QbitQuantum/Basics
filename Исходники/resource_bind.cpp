//void loadResource(Resource* resource)
void manualresourceloader_load_resource(ManualResourceLoaderHandle handle, coiResourceHandle resource)
{
    Ogre::ManualResourceLoader* loader = static_cast<Ogre::ManualResourceLoader*>(handle);
    Ogre::Resource* res = static_cast<Ogre::Resource*>(resource);
    loader->loadResource(res);
}