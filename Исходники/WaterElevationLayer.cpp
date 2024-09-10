    WaterElevationLayerResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc,
            const TiXmlElement *e = NULL) :
        ResourceTemplate<40, WaterElevationLayer> (manager, name, desc)
    {
        e = e == NULL ? desc->descriptor : e;
        ptr<GraphProducer> graphProducer;
        ptr<TileProducer> elevations;
        int displayLevel = 0;
        bool quality = true;
        bool deform = false;

        checkParameters(desc, e, "name,graph,renderProg,fillProg,level,cpuElevations,quality,deform,");

        string g = getParameter(desc, e, "graph");
        graphProducer = manager->loadResource(g).cast<GraphProducer>();

        string r = getParameter(desc, e, "cpuElevations");
        elevations = manager->loadResource(r).cast<TileProducer>();

        if (e->Attribute("level") != NULL) {
            getIntParameter(desc, e, "level", &displayLevel);
        }
        if (e->Attribute("quality") != NULL) {
            quality = strcmp(e->Attribute("quality"), "true") == 0;
        }
        if (e->Attribute("deform") != NULL) {
            deform = strcmp(e->Attribute("deform"), "true") == 0;
        }

        ptr<Program> layerProgram = manager->loadResource(getParameter(desc, e, "renderProg")).cast<Program>();
        ptr<Program> fillProg = manager->loadResource(getParameter(desc, e, "fillProg")).cast<Program>();
        init(graphProducer, layerProgram, fillProg, elevations, displayLevel, quality, deform);
    }