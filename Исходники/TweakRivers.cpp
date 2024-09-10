    TweakRiversResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc,
            const TiXmlElement *e = NULL) :
        ResourceTemplate<55, TweakRivers> (manager, name, desc)
    {
        e = e == NULL ? desc->descriptor : e;
        checkParameters(desc, e, "name,drawer,active,");

        ptr<DrawRiversTask> drawer = manager->loadResource(getParameter(desc, e, "drawer")).cast<DrawRiversTask>();
        assert(drawer != NULL);
        assert(drawer.cast<DrawRiversTask>() != NULL);

        bool active = true;
        if (e->Attribute("active") != NULL) {
            active = strcmp(e->Attribute("active"), "true") == 0;
        }
        init(drawer, active);
    }