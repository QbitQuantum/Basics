    void FullScreenPass::init(const std::string& vsFile, const std::string& psFile, const Program::DefineList& programDefines, bool disableDepth, bool disableStencil, uint32_t viewportMask, bool enableSPS)
    {
        mpPipelineState = GraphicsState::create();
        mpPipelineState->toggleSinglePassStereo(enableSPS);

        // create depth stencil state
        DepthStencilState::Desc dsDesc;
        dsDesc.setDepthTest(!disableDepth);
        dsDesc.setDepthWriteMask(!disableDepth);
        dsDesc.setDepthFunc(DepthStencilState::Func::LessEqual);    // Equal is needed to allow overdraw when z is enabled (e.g., background pass etc.)
        dsDesc.setStencilTest(!disableStencil);
        dsDesc.setStencilWriteMask(!disableStencil);
        mpDepthStencilState = DepthStencilState::create(dsDesc);

        Program::DefineList defs = programDefines;
        std::string gs;

        if(viewportMask)
        {
            defs.add("_VIEWPORT_MASK", std::to_string(viewportMask));
            if(checkForViewportArray2Support())
            {
                defs.add("_USE_VP2_EXT");
            }
            else
            {
                defs.add("_OUTPUT_VERTEX_COUNT", std::to_string(3 * __popcnt(viewportMask)));
#ifdef FALCOR_VK
                gs = "Framework/Shaders/FullScreenPass.gs.glsl";
#else
                gs = "Framework/Shaders/FullScreenPass.gs.slang";
#endif
            }
        }

        const std::string vs(vsFile.empty() ? "Framework/Shaders/FullScreenPass.vs.slang" : vsFile);
        mpProgram = GraphicsProgram::createFromFile(vs, psFile, gs, "", "", defs);
        mpPipelineState->setProgram(mpProgram);

        if (FullScreenPass::spVertexBuffer == nullptr)
        {
            initStaticObjects(spVertexBuffer, spVao);
        }
        mpPipelineState->setVao(FullScreenPass::spVao);
    }