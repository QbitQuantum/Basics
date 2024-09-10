    virtual void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
    {
        switch (event)
        {
        case eFE_Initialize:
            break;
        case eFE_Activate:
            IGameFramework* pGameFramework = gEnv->pGame->GetIGameFramework();

            if(IsPortActive(pActInfo, EIP_Cast))
            {
                // setup ray + optionally skip 1 entity
                ray_hit rayHit;
                static const float maxRayDist = 100.f;
                const unsigned int flags = rwi_stop_at_pierceable|rwi_colltype_any;
                IPhysicalEntity	*skipList[1];
                int skipCount = 0;
                IEntity* skipEntity = gEnv->pEntitySystem->GetEntity(GetPortEntityId(pActInfo, EIP_SkipEntity));
                if(skipEntity)
                {
                    skipList[0] = skipEntity->GetPhysics();
                    skipCount = 1;
                }

                Vec3 rayPos = GetPortVec3(pActInfo, EIP_RayPos);
                Vec3 rayDir = GetPortVec3(pActInfo, EIP_RayDir);

                // Check if the ray hits an entity
                if(gEnv->pSystem->GetIPhysicalWorld()->RayWorldIntersection(rayPos, rayDir * 100, ent_all, flags, &rayHit, 1, skipList, skipCount))
                {
                    int type = rayHit.pCollider->GetiForeignData();

                    if (type == PHYS_FOREIGN_ID_ENTITY)
                    {
                        IEntity* pEntity = (IEntity*)rayHit.pCollider->GetForeignData(PHYS_FOREIGN_ID_ENTITY);
                        IEntityRenderProxy* pRenderProxy = pEntity ? (IEntityRenderProxy*)pEntity->GetProxy(ENTITY_PROXY_RENDER) : 0;

                        // Get the renderproxy, and use it to check if the material is a DynTex, and get the UIElement if so
                        if(pRenderProxy)
                        {
                            IRenderNode *pRenderNode = pRenderProxy->GetRenderNode();
                            IMaterial* pMaterial = pRenderProxy->GetRenderMaterial();
                            SEfResTexture* texture = 0;
                            if(pMaterial && pMaterial->GetShaderItem().m_pShaderResources)
                                texture= pMaterial->GetShaderItem().m_pShaderResources->GetTexture(EFTT_DIFFUSE);
                            IUIElement* pElement = texture ? gEnv->pFlashUI->GetUIElementByInstanceStr(texture->m_Name) : 0;

                            if(pElement && pRenderNode)
                            {
                                int m_dynTexGeomSlot = 0;
                                IStatObj* pObj = pRenderNode->GetEntityStatObj(m_dynTexGeomSlot);

                                // result
                                bool hasHit = false;
                                Vec2 uv0, uv1, uv2;
                                Vec3 p0, p1, p2;
                                Vec3 hitpos;


                                // calculate ray dir
                                CCamera cam = gEnv->pRenderer->GetCamera();
                                if (pEntity->GetSlotFlags(m_dynTexGeomSlot) & ENTITY_SLOT_RENDER_NEAREST)
                                {
                                    ICVar *r_drawnearfov = gEnv->pConsole->GetCVar("r_DrawNearFoV");
                                    assert(r_drawnearfov);
                                    cam.SetFrustum(cam.GetViewSurfaceX(),cam.GetViewSurfaceZ(),DEG2RAD(r_drawnearfov->GetFVal()),cam.GetNearPlane(),cam.GetFarPlane(), cam.GetPixelAspectRatio());
                                }

                                Vec3 vPos0 = rayPos;
                                Vec3 vPos1 = rayPos + rayDir;

                                // translate into object space
                                const Matrix34 m = pEntity->GetWorldTM().GetInverted();
                                vPos0 = m * vPos0;
                                vPos1 = m * vPos1;

                                // walk through all sub objects
                                const int objCount = pObj->GetSubObjectCount();
                                for (int obj = 0; obj <= objCount && !hasHit; ++obj)
                                {
                                    Vec3 vP0, vP1;
                                    IStatObj* pSubObj = NULL;

                                    if (obj == objCount)
                                    {
                                        vP0 = vPos0;
                                        vP1 = vPos1;
                                        pSubObj = pObj;
                                    }
                                    else
                                    {
                                        IStatObj::SSubObject* pSub = pObj->GetSubObject(obj);
                                        const Matrix34 mm = pSub->tm.GetInverted();
                                        vP0 = mm * vPos0;
                                        vP1 = mm * vPos1;
                                        pSubObj = pSub->pStatObj;
                                    }

                                    IRenderMesh* pMesh = pSubObj ? pSubObj->GetRenderMesh() : NULL;
                                    if (pMesh)
                                    {
                                        const Ray ray(vP0, (vP1-vP0).GetNormalized() * maxRayDist);
                                        hasHit = RayIntersectMesh(pMesh, pMaterial, pElement, ray, hitpos, p0, p1, p2, uv0, uv1, uv2);
                                    }
                                }

                                // skip if not hit
                                if (!hasHit)
                                {
                                    ActivateOutput(pActInfo, EOP_Failed, 1);
                                    return;
                                }

                                // calculate vectors from hitpos to vertices p0, p1 and p2:
                                const Vec3 v0 = p0-hitpos;
                                const Vec3 v1 = p1-hitpos;
                                const Vec3 v2 = p2-hitpos;

                                // calculate factors
                                const float h = (p0-p1).Cross(p0-p2).GetLength();
                                const float f0 = v1.Cross(v2).GetLength() / h;
                                const float f1 = v2.Cross(v0).GetLength() / h;
                                const float f2 = v0.Cross(v1).GetLength() / h;

                                // find the uv corresponding to hitpos
                                Vec3 uv = uv0 * f0 + uv1 * f1 + uv2 * f2;

                                // translate to flash space
                                int x, y, width, height;
                                float aspect;
                                pElement->GetFlashPlayer()->GetViewport(x, y, width, height, aspect);
                                int iX = int_round(uv.x * (float)width);
                                int iY = int_round(uv.y * (float)height);

                                // call the function provided if it is present in the UIElement description
                                string funcName = GetPortString(pActInfo, EIP_CallFunction);
                                const SUIEventDesc* eventDesc = pElement->GetFunctionDesc(funcName);
                                if(eventDesc)
                                {
                                    SUIArguments arg;
                                    arg.AddArgument(iX);
                                    arg.AddArgument(iY);
                                    pElement->CallFunction(eventDesc->sName, arg);
                                }

                                ActivateOutput(pActInfo, EOP_Success, 1);
                            }
                        }
                    }
                }

                ActivateOutput(pActInfo, EOP_Failed, 1);
            }

            break;
        }
    }