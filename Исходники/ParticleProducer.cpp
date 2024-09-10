    ParticleProducerResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc, const TiXmlElement *e = NULL) :
        ResourceTemplate<50, ParticleProducer>(manager, name, desc)
    {
        e = e == NULL ? desc->descriptor : e;
        checkParameters(desc, e, "name,storage,");

        ptr<ParticleStorage> storage = manager->loadResource(getParameter(desc, e, "storage")).cast<ParticleStorage>();

        const TiXmlNode *n = e->FirstChild();
        while (n != NULL) {
            const TiXmlElement *f = n->ToElement();
            if (f == NULL) {
                n = n->NextSibling();
                continue;
            }

            ptr<ParticleLayer> l = manager->loadResource(desc, f).cast<ParticleLayer>();
            if (l != NULL) {
                addLayer(l);
            } else {
                if (Logger::WARNING_LOGGER != NULL) {
                    log(Logger::WARNING_LOGGER, desc, f, "Unknown scene node element '" + f->ValueStr() + "'");
                }
            }
            n = n->NextSibling();
        }

        init(storage);

    }