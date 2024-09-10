    OrthoGPUProducerResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc,
            const TiXmlElement *e = NULL) :
        ResourceTemplate<3, OrthoGPUProducer> (manager, name, desc)
    {
        e = e == NULL ? desc->descriptor : e;
        ptr<TileCache> cache;
        ptr<TileCache> backgroundCache;
        ptr<TileProducer> ortho;
        int maxLevel = -1;
        ptr<Texture2D> compressedTexture;
        ptr<Texture2D> uncompressedTexture;
        checkParameters(desc, e, "name,cache,backgroundCache,ortho,maxLevel,");
        cache = manager->loadResource(getParameter(desc, e, "cache")).cast<TileCache>();
        if (e->Attribute("backgroundCache") != NULL) {
            backgroundCache = manager->loadResource(getParameter(desc, e, "backgroundCache")).cast<TileCache>();
        }
        if (e->Attribute("ortho") != NULL) {
            ortho = manager->loadResource(getParameter(desc, e, "ortho")).cast<TileProducer>();
        }
        if (e->Attribute("maxLevel") != NULL) {
            getIntParameter(desc, e, "maxLevel", &maxLevel);
        }

        bool hasLayers = false;
        const TiXmlNode *n = e->FirstChild();
        while (n != NULL) {
            const TiXmlElement *f = n->ToElement();
            if (f == NULL) {
                n = n->NextSibling();
                continue;
            }

            ptr<TileLayer> l = manager->loadResource(desc, f).cast<TileLayer>();

            if (l != NULL) {
                addLayer(l);
                hasLayers = true;
            } else {
                if (Logger::WARNING_LOGGER != NULL) {
                    log(Logger::WARNING_LOGGER, desc, f, "Unknown scene node element '" + f->ValueStr() + "'");
                }
            }
            n = n->NextSibling();
        }

        if (ortho != NULL && ortho.cast<OrthoCPUProducer> ()->isCompressed()) {
            int tileSize = ortho->getCache()->getStorage()->getTileSize();
            int channels = ortho->getCache()->getStorage().cast<CPUTileStorage<unsigned char> >()->getChannels();
            assert(tileSize == cache->getStorage()->getTileSize());
            assert(channels >= 3);
            ostringstream compTex;
            compTex << "renderbuffer-" << tileSize << "-" << (channels == 3 ? "COMPRESSED_RGB_S3TC_DXT1_EXT" : "COMPRESSED_RGBA_S3TC_DXT5_EXT");
            compressedTexture = manager->loadResource(compTex.str()).cast<Texture2D>();
        }

        if ((ortho != NULL && ortho.cast<OrthoCPUProducer>()->isCompressed()) || hasLayers) {
            int tileSize = cache->getStorage()->getTileSize();
            int channels = cache->getStorage().cast<GPUTileStorage>()->getTexture(0)->getComponents();
            ostringstream uncompTex;
            uncompTex << "renderbuffer-" << tileSize << "-" << (channels == 3 ? "RGB8" : "RGBA8");
            uncompressedTexture = manager->loadResource(uncompTex.str()).cast<Texture2D>();
        }

        assert(ortho != NULL || hasLayers);

        init(cache, backgroundCache, ortho, maxLevel, compressedTexture, uncompressedTexture);
    }