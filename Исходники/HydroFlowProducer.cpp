    HydroFlowProducerResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc, const TiXmlElement *e = NULL) :
        ResourceTemplate<30, HydroFlowProducer>(manager, name, desc)
    {
        e = e == NULL ? desc->descriptor : e;
        ptr<TileCache> cache;
        ptr<GraphProducer> graphs;
        int displayTileSize = 192;
        float slip = 1.0f;
        float searchRadiusFactor = 1.0f;
        float potentialDelta = 0.01f;
        int minLevel = 0;

        checkParameters(desc, e, "name,cache,graphs,displayTileSize,slip,searchRadiusFactor, potentialDelta,minLevel,");
        cache = manager->loadResource(getParameter(desc, e, "cache")).cast<TileCache>();
        graphs = manager->loadResource(getParameter(desc, e, "graphs")).cast<GraphProducer>();
        if (e->Attribute("displayTileSize") != NULL) {
            getIntParameter(desc, e, "displayTileSize", &displayTileSize);
        }
        if (e->Attribute("slip") != NULL) {
            getFloatParameter(desc, e, "slip", &slip);
        }
        if (e->Attribute("searchRadiusFactor") != NULL) {
            getFloatParameter(desc, e, "searchRadiusFactor", &searchRadiusFactor);
        }
        if (e->Attribute("potentialDelta") != NULL) {
            getFloatParameter(desc, e, "potentialDelta", &potentialDelta);
        }
        if (e->Attribute("minLevel") != NULL) {
            getIntParameter(desc, e, "minLevel", &minLevel);
        }

        init(graphs, cache, displayTileSize, slip, searchRadiusFactor, potentialDelta, minLevel);
    }