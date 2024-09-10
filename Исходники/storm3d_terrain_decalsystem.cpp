    void render(Storm3D_Scene &scene)
    {
        gfx::Renderer& renderer = storm.renderer;
        gfx::Device& device = renderer.device;
        gfx::ProgramManager& programManager = renderer.programManager;

        baseDecalVertex = 0;

        findDecals(scene);
        if (decals.empty())
            return;

        Vertex_P3NDUV *buffer = 0;
        renderer.lockDynVtx<Vertex_P3NDUV>(decals.size() * 4, &buffer, &baseDecalVertex);
        for (unsigned int i = 0; i < decals.size(); ++i)
        {
            Decal& decal = *decals[i];
            COL decalColor = 
                decal.light * (decal.type == Outside ? outFactor : inFactor);
            decalColor.Clamp();
            uint32_t vertexColor = decalColor.as_u32_D3D_ARGB(decal.alpha);

            decal.insert(buffer, vertexColor);
            buffer += 4;
        }
        renderer.unlockDynVtx();

        // Render
        if (!decals.empty())
        {
            device.SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
            device.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
            device.SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
            device.SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            device.SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

            D3DXMATRIX tm;
            D3DXMatrixIdentity(&tm);
            programManager.setWorldMatrix(tm);
            programManager.setProgram(gfx::ProgramManager::DECAL_LIGHTING);

            renderer.setDynVtxBuffer<Vertex_P3NDUV>();
            renderer.setFVF(FVF_P3NDUV);

            int materialIndex = 0;
            int startIndex = 0;
            int endIndex = 0;


            for (;;)
            {
                materialIndex = decals[startIndex]->materialIndex;
                if(materials[materialIndex].baseTexture)
                    materials[materialIndex].baseTexture->Apply(0);
                programManager.setDiffuse(materials[materialIndex].diffuseColor);
                programManager.applyState(device);

                int decalAmount = decals.size();
                for (int i = startIndex + 1; i < decalAmount; ++i)
                {
                    if (decals[i]->materialIndex != materialIndex)
                        break;

                    endIndex = i;
                }

                int renderAmount = endIndex - startIndex + 1;

                renderer.drawQuads(baseDecalVertex + startIndex * 4, renderAmount);

                startIndex = ++endIndex;

                if (startIndex >= decalAmount)
                    break;
            }

            device.SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        }
    }