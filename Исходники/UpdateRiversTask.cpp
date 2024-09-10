    UpdateRiversTaskResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc, const TiXmlElement *e = NULL) :
        ResourceTemplate<50, UpdateRiversTask>(manager, name, desc)
    {
        e = e == NULL ? desc->descriptor : e;
        float timeStep = 1.0f;
        checkParameters(desc, e, "name,particles,timeStep,");

        if (e->Attribute("timeStep") != NULL) {
            getFloatParameter(desc, e, "timeStep", &timeStep);
        }

        ptr<ParticleProducer> particles = manager->loadResource(getParameter(desc, e, "particles")).cast<ParticleProducer>();
        assert(particles != NULL);

        init(particles, timeStep);
    }