    TextureOrthoLayerResource(ptr<ResourceManager> manager, const string &name, ptr<ResourceDescriptor> desc,
            const TiXmlElement *e = NULL) :
        ResourceTemplate<40, TextureLayer> (manager, name, desc)
    {
        e = e == NULL ? desc->descriptor : e;

        checkParameters(desc, e, "name,producer,renderProg,tileSamplerName,storeTiles,equation,sourceFunction,destinationFunction,equationAlpha,sourceFunctionAlpha,destinationFunctionAlpha,level,");

        ptr<Object> programRessource = manager->loadResource(getParameter(desc, e, "renderProg"));
        assert(programRessource != NULL);
        ptr<Program> program = programRessource.cast<Program>();
        assert(program != NULL);

        ptr<TileProducer> tiles = manager->loadResource(getParameter(desc, e, "producer")).cast<TileProducer>();
        assert(tiles != NULL);

        std::string tileSamplerName = getParameter(desc, e, "tileSamplerName");
        assert(tileSamplerName != "");

        BlendParams blendParams;
        blendParams.rgb = ADD;
        blendParams.srgb = SRC_ALPHA;
        blendParams.drgb = ONE_MINUS_SRC_ALPHA;
        blendParams.alpha = ADD;
        blendParams.salpha = SRC_ALPHA;
        blendParams.dalpha = ONE_MINUS_SRC_ALPHA;
        const char *c = e->Attribute("buffer");
        if (c != NULL) {
            if (strcmp(c, "COLOR0") == 0) {
                blendParams.buffer = COLOR0;
            } else if (strcmp(c, "COLOR1") == 0) {
                blendParams.buffer = COLOR1;
            } else if (strcmp(c, "COLOR2") == 0) {
                blendParams.buffer = COLOR2;
            } else if (strcmp(c, "COLOR3") == 0) {
                blendParams.buffer = COLOR3;
            } else if (strcmp(c, "DEPTH") == 0) {
                blendParams.buffer = DEPTH;
            } else if (strcmp(c, "STENCIL") == 0) {
                blendParams.buffer = STENCIL;
            }
        }
        if (e->Attribute("equation") != NULL) {
            blendParams.rgb = getBlendEquation(desc, e, "equation");
            blendParams.srgb = getBlendArgument(desc, e, "sourceFunction");
            blendParams.drgb = getBlendArgument(desc, e, "destinationFunction");
        }
        if (e->Attribute("equationAlpha") != NULL) {
            blendParams.alpha = getBlendEquation(desc, e, "equationAlpha");
            blendParams.salpha = getBlendArgument(desc, e, "sourceFunctionAlpha");
            blendParams.dalpha = getBlendArgument(desc, e, "destinationFunctionAlpha");
        }

        int displayLevel = 0;
        if (e->Attribute("level") != NULL) {
            getIntParameter(desc, e, "level", &displayLevel);
        }

        bool storeTiles = false;
        if (e->Attribute("storeTiles") != NULL) {
            storeTiles = strcmp(e->Attribute("storeTiles"), "true") == 0;
        }

        init(tiles, program, tileSamplerName, blendParams, displayLevel, storeTiles);
    }