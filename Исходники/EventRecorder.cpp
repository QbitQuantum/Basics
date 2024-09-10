    EventRecorderResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc, const TiXmlElement *e = NULL) :
        ResourceTemplate<100, EventRecorder> (manager, name, desc)
    {
        e = e == NULL ? desc->descriptor : e;
        checkParameters(desc, e, "name,recorded,eventFile,autoSave,videoDirectory,cursorTexture,next,");

        recorded = getParameter(desc, e, "recorded");
        const char *eventFile = e->Attribute("eventFile");
        bool autoSave = e->Attribute("autoSave") != NULL && strcmp(e->Attribute("autoSave"), "true") == 0;
        const char *frames = e->Attribute("videoDirectory");
        ptr<Program> prog = manager->loadResource("copyShader;").cast<Program>();
        ptr<Texture2D> cursor = manager->loadResource(getParameter(desc, e, "cursorTexture")).cast<Texture2D>();
        ptr<EventHandler> next = manager->loadResource(getParameter(desc, e, "next")).cast<EventHandler>();

        init(eventFile, autoSave, frames, prog, cursor, next);
    }